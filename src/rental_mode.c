#include "global.h"
#include "random.h"
#include "string_util.h"
#include "pokemon.h"
#include "move.h"
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
    GenerateRentalOffer();
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

// Script special: start a run and open the draft screen. Format/cap are hardcoded to
// Singles / 0 restricted for this first cut; a format-select menu is a quick follow-up.
// Called from the lobby attendant script, followed by `waitstate`.
void StartRentalDraft(void)
{
    RentalRun_Begin(RENTAL_FORMAT_SINGLES, 0);
    DoRentalDraftScreen();
}
