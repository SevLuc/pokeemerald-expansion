#include "global.h"
#include "random.h"
#include "string_util.h"
#include "pokemon.h"
#include "move.h"
#include "battle.h"
#include "battle_frontier.h"
#include "event_data.h"
#include "constants/battle_frontier.h"
#include "battle_tower_rental.h"
#include "rental_mode.h"

// Standalone rental battle mode.
//
// This file will grow into the mode's controller (draft, team preview, recruit).
// For the M2 skeleton it holds a single script special that proves the generated
// rental pool (gRentalMons, from tools/gen_rental_mons.py) is compiled into the
// ROM and indexable at run time.

// Script special: pick a random set from the rental pool and buffer its species
// name into gStringVar1 and its first move's name into gStringVar2, so a lobby
// script can display them. If the message shows a real species and move, the whole
// M0 data pipeline (JSON -> generated table -> in-game) is working end to end.
void BufferRandomRentalMon(void)
{
    u32 index = Random() % NUM_RENTAL_MONS;
    const struct TrainerMon *set = &gRentalMons[index];

    StringCopy(gStringVar1, GetSpeciesName(set->species));
    StringCopy(gStringVar2, GetMoveName(set->moves[0]));
}

// ------------------------------------------------------------------------------
// Draft state and offer generation (M3 foundation).
//
// The draft screen (adapted from the Battle Factory select screen) sits on top of
// this. Kept separate and UI-free so it can be reasoned about and adjusted without
// touching graphics code.
// ------------------------------------------------------------------------------

struct RentalRun gRentalRun;

static bool32 OfferHasSpeciesOrItem(u32 count, u32 species, u32 item)
{
    u32 i;
    for (i = 0; i < count; i++)
    {
        const struct TrainerMon *o = &gRentalMons[gRentalRun.offer[i]];
        if (o->species == species || o->heldItem == item)
            return TRUE;
    }
    return FALSE;
}

void GenerateRentalOffer(void)
{
    u32 count = 0;
    u32 restrictedCount = 0;
    u32 guard = 0;

    // Draw distinct-species, distinct-item sets, capping the restricted-tier ones
    // at restrictedCap. The guard bounds the loop in the unlikely event the pool
    // cannot satisfy the constraints (it easily can with thousands of sets).
    while (count < RENTAL_OFFER_SIZE && guard < 100000)
    {
        u32 index = Random() % NUM_RENTAL_MONS;
        const struct TrainerMon *set = &gRentalMons[index];
        bool32 restricted = IsRentalTierRestricted(gRentalMonTier[index]);

        guard++;

        if (restricted && restrictedCount >= gRentalRun.restrictedCap)
            continue;
        if (OfferHasSpeciesOrItem(count, set->species, set->heldItem))
            continue;

        gRentalRun.offer[count++] = index;
        if (restricted)
            restrictedCount++;
    }

    gRentalRun.offerCount = count;
}

void RentalRun_Begin(u8 format, u8 restrictedCap)
{
    gRentalRun.format = format;
    gRentalRun.restrictedCap = restrictedCap;
    gRentalRun.rosterCount = 0;
    gRentalRun.bringCount = (format == RENTAL_FORMAT_DOUBLES) ? 4 : 3;
    gRentalRun.winStreak = 0;
    GenerateRentalOffer();
    // The per-battle opponent is rolled by RentalPrepareNextBattle inside the run
    // loop (so each battle faces a fresh team), not here.
}

bool32 RentalRoster_TryAdd(u32 offerSlot)
{
    u32 i;
    u32 index;
    const struct TrainerMon *set;
    u32 restrictedCount = 0;

    if (offerSlot >= gRentalRun.offerCount || gRentalRun.rosterCount >= RENTAL_ROSTER_SIZE)
        return FALSE;

    index = gRentalRun.offer[offerSlot];
    set = &gRentalMons[index];

    // Species + Item clause against the current roster; tally its restricted mons.
    for (i = 0; i < gRentalRun.rosterCount; i++)
    {
        const struct TrainerMon *r = &gRentalMons[gRentalRun.roster[i]];
        if (r->species == set->species || r->heldItem == set->heldItem)
            return FALSE;
        if (IsRentalTierRestricted(gRentalMonTier[gRentalRun.roster[i]]))
            restrictedCount++;
    }

    if (IsRentalTierRestricted(gRentalMonTier[index]) && restrictedCount >= gRentalRun.restrictedCap)
        return FALSE;

    gRentalRun.roster[gRentalRun.rosterCount++] = index;
    return TRUE;
}

void RentalRoster_Remove(u32 rosterSlot)
{
    u32 i;

    if (rosterSlot >= gRentalRun.rosterCount)
        return;

    for (i = rosterSlot; i + 1 < gRentalRun.rosterCount; i++)
        gRentalRun.roster[i] = gRentalRun.roster[i + 1];
    gRentalRun.rosterCount--;
}

static bool32 ArrayHasSpeciesOrItem(const u16 *arr, u32 count, u32 species, u32 item)
{
    u32 i;
    for (i = 0; i < count; i++)
    {
        const struct TrainerMon *o = &gRentalMons[arr[i]];
        if (o->species == species || o->heldItem == item)
            return TRUE;
    }
    return FALSE;
}

void GenerateRentalOpponent(void)
{
    u32 count = 0;
    u32 restrictedCount = 0;
    u32 guard = 0;

    while (count < RENTAL_ROSTER_SIZE && guard < 100000)
    {
        u32 index = Random() % NUM_RENTAL_MONS;
        const struct TrainerMon *set = &gRentalMons[index];
        bool32 restricted = IsRentalTierRestricted(gRentalMonTier[index]);

        guard++;

        if (restricted && restrictedCount >= gRentalRun.restrictedCap)
            continue;
        if (ArrayHasSpeciesOrItem(gRentalRun.oppRoster, count, set->species, set->heldItem))
            continue;

        gRentalRun.oppRoster[count++] = index;
        if (restricted)
            restrictedCount++;
    }

    gRentalRun.oppRosterCount = count;
}

static const u8 sText_RentalComma[] = _(", ");

// Script special: buffer the species names of the opponent's fielded team into
// gStringVar1 (comma-separated) for a team-preview message before the player picks
// which mons to bring.
void BufferRentalOpponentPreview(void)
{
    u32 i;
    u32 n = gRentalRun.bringCount;

    if (n == 0 || n > gRentalRun.oppRosterCount)
        n = gRentalRun.oppRosterCount;
    if (n == 0)
        return;

    StringCopy(gStringVar1, GetSpeciesName(gRentalMons[gRentalRun.oppRoster[0]].species));
    for (i = 1; i < n; i++)
    {
        StringAppend(gStringVar1, sText_RentalComma);
        StringAppend(gStringVar1, GetSpeciesName(gRentalMons[gRentalRun.oppRoster[i]].species));
    }
}

// ------------------------------------------------------------------------------
// Run loop: draft once, then fight successive opponents until a loss, tracking a
// win streak. The bring-N reduce is destructive, so the full drafted six are stashed
// before each battle and restored (at full HP) after, keeping the same team for the
// whole run.
// ------------------------------------------------------------------------------

static EWRAM_DATA struct Pokemon sRentalSavedParty[PARTY_SIZE] = {0};

void RentalPrepareNextBattle(void)
{
    GenerateRentalOpponent();
}

void RentalSaveFullParty(void)
{
    u32 i;
    for (i = 0; i < PARTY_SIZE; i++)
        sRentalSavedParty[i] = gParties[B_TRAINER_PLAYER][i];
}

void RentalRestoreFullParty(void)
{
    u32 i;
    for (i = 0; i < PARTY_SIZE; i++)
        gParties[B_TRAINER_PLAYER][i] = sRentalSavedParty[i];
    CalculatePlayerPartyCount();
}

void RentalOnWin(void)
{
    if (gRentalRun.winStreak < 0xFFFF)
        gRentalRun.winStreak++;
    RentalBufferStreak();
}

void RentalBufferStreak(void)
{
    ConvertIntToDecimalStringN(gStringVar1, gRentalRun.winStreak, STR_CONV_MODE_LEFT_ALIGN, 4);
}

// ------------------------------------------------------------------------------
// Recruit: after a win, take one of the opponent's fielded mons in place of one of
// yours (clause- and cap-safe). The script offers each opponent mon in turn
// (BufferRentalRecruitCandidate) and, on acceptance, has the player pick which of
// their team to release (via the ChoosePartyMon party menu), then applies the swap
// (RentalDoRecruit).
// ------------------------------------------------------------------------------

static u32 RentalFieldCount(void)
{
    u32 n = gRentalRun.bringCount;
    if (n == 0 || n > gRentalRun.oppRosterCount)
        n = gRentalRun.oppRosterCount;
    return n;
}

// TRUE if putting newMon into the roster (replacing skipSlot) keeps Species Clause,
// Item Clause, and the restricted cap.
static bool32 RentalRecruitClauseOK(u32 newMon, u32 skipSlot)
{
    u32 i, restrictedCount = 0;
    for (i = 0; i < gRentalRun.rosterCount; i++)
    {
        if (i == skipSlot)
            continue;
        if (gRentalMons[gRentalRun.roster[i]].species == gRentalMons[newMon].species)
            return FALSE;
        if (gRentalMons[gRentalRun.roster[i]].heldItem == gRentalMons[newMon].heldItem)
            return FALSE;
        if (IsRentalTierRestricted(gRentalMonTier[gRentalRun.roster[i]]))
            restrictedCount++;
    }
    if (IsRentalTierRestricted(gRentalMonTier[newMon]) && restrictedCount >= gRentalRun.restrictedCap)
        return FALSE;
    return TRUE;
}

// Script special: buffer opponent mon VAR_0x8006's species into gStringVar1 for the
// "recruit this one?" prompt. VAR_RESULT = TRUE while the index is a real candidate,
// FALSE once the list is exhausted.
void BufferRentalRecruitCandidate(void)
{
    u32 i = gSpecialVar_0x8006;

    if (i >= RentalFieldCount())
    {
        gSpecialVar_Result = FALSE;
        return;
    }
    StringCopy(gStringVar1, GetSpeciesName(gRentalMons[gRentalRun.oppRoster[i]].species));
    gSpecialVar_Result = TRUE;
}

// Script special: replace roster slot VAR_0x8004 with opponent mon VAR_0x8006, if
// clause- and cap-legal. VAR_RESULT = TRUE on success, FALSE if it would break a rule.
void RentalDoRecruit(void)
{
    u32 oppIdx = gSpecialVar_0x8006;
    u32 slot = gSpecialVar_0x8004;
    u32 newMon;

    if (oppIdx >= RentalFieldCount() || slot >= gRentalRun.rosterCount)
    {
        gSpecialVar_Result = FALSE;
        return;
    }
    newMon = gRentalRun.oppRoster[oppIdx];
    if (!RentalRecruitClauseOK(newMon, slot))
    {
        gSpecialVar_Result = FALSE;
        return;
    }
    gRentalRun.roster[slot] = newMon;
    CreateFacilityMon(&gRentalMons[newMon], FRONTIER_MAX_LEVEL_50, 31, 0, FLAG_FRONTIER_MON_FACTORY,
            &gParties[B_TRAINER_PLAYER][slot]);
    CalculatePlayerPartyCount();
    gSpecialVar_Result = TRUE;
}

// Script special: start a run and open the draft screen. Format/cap are hardcoded to
// Singles / 0 restricted for this first cut; a format-select menu is a quick follow-up.
// Called from the lobby attendant script, followed by `waitstate`.
void StartRentalDraft(void)
{
    u32 format = (gSpecialVar_0x8004 != 0) ? RENTAL_FORMAT_DOUBLES : RENTAL_FORMAT_SINGLES;
    u32 cap = gSpecialVar_0x8005; // restricted cap chosen by the lobby script (0/1/2)
    if (cap > 2)
        cap = 0;
    RentalRun_Begin(format, cap);
    DoRentalDraftScreen();
}

// Script special: put the current run's bring count (3 singles / 4 doubles) into
// VAR_0x8005 so the party-select prompt asks for the right number.
void RentalSetBringCountVar(void)
{
    gSpecialVar_0x8005 = gRentalRun.bringCount;
}
