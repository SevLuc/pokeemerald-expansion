#ifndef GUARD_RENTAL_MODE_H
#define GUARD_RENTAL_MODE_H

#include "battle_tower_rental.h"

// Standalone rental battle mode (see docs/battle-tower/phase-1-implementation-plan.md).

#define RENTAL_OFFER_SIZE   12  // mons offered at the draft
#define RENTAL_ROSTER_SIZE  6   // mons the player keeps

enum RentalFormat
{
    RENTAL_FORMAT_SINGLES,  // roster 6, bring 3
    RENTAL_FORMAT_DOUBLES,  // roster 6, bring 4
};

// In-RAM state for one rental run. Persistence is deferred to a later milestone
// (the cartridge flash is full and the run format is still settling), so for now
// this lives in RAM and is lost on power-off. Indices below are into gRentalMons.
struct RentalRun
{
    u16 offer[RENTAL_OFFER_SIZE];    // the draft's 12 offered sets
    u16 roster[RENTAL_ROSTER_SIZE];  // the 6 the player kept
    u16 oppRoster[RENTAL_ROSTER_SIZE]; // the opponent's team this battle (gRentalMons indices)
    u8 offerCount;
    u8 rosterCount;
    u8 oppRosterCount;
    u8 format;         // enum RentalFormat
    u8 restrictedCap;  // 0 / 1 / 2 restricted-tier mons allowed
    u8 bringCount;     // 3 (singles) or 4 (doubles) brought per battle
    u16 winStreak;     // battles won so far this run
};

extern struct RentalRun gRentalRun;

// TRUE while a standalone rental session is active (see rental_mode.c).
extern bool8 gRentalModeActive;

// Start a fresh run: record the format + cap, clear the roster, and roll a draft
// offer of RENTAL_OFFER_SIZE clause-legal sets.
void RentalRun_Begin(u8 format, u8 restrictedCap);

// Roll RENTAL_OFFER_SIZE offered sets into gRentalRun.offer. Every offered set has
// a distinct species and a distinct held item, and at most restrictedCap of them
// are restricted-tier, so ANY 6 the player picks already satisfy Species Clause,
// Item Clause, and the restricted cap.
void GenerateRentalOffer(void);

// Add offer slot [offerSlot] (0..offerCount-1) to the roster if it fits. With the
// offer generated as above the check always passes, but it is kept so a future,
// looser offer still cannot violate the rules. Returns TRUE on success.
bool32 RentalRoster_TryAdd(u32 offerSlot);

// Remove a roster slot (0..rosterCount-1), compacting the rest down.
void RentalRoster_Remove(u32 rosterSlot);

// Roll the opponent's team into gRentalRun.oppRoster: RENTAL_ROSTER_SIZE sets with
// distinct species and items, at most restrictedCap restricted, so it obeys the same
// clauses/cap as the player. Called by RentalRun_Begin so team preview can show it.
void GenerateRentalOpponent(void);

// Script special: buffer the opponent's fielded species names into gStringVar1 for a
// team-preview message.
void BufferRentalOpponentPreview(void);

// Run-loop script specials.
void RentalPrepareNextBattle(void); // roll a fresh opponent for the next battle
void RentalSaveFullParty(void);     // stash the full 6 before the bring-N reduce
void RentalRestoreFullParty(void);  // restore the full 6 (healed) after the battle
void RentalOnWin(void);             // increment the win streak
void RentalBufferStreak(void);      // buffer the current streak into gStringVar1

// Recruit script specials.
void BufferRentalRecruitCandidate(void); // buffer opponent VAR_0x8006's species name
void RentalDoRecruit(void);              // swap roster slot VAR_0x8004 for opp VAR_0x8006

// Recruit-board helpers (used by src/rental_recruit_screen.c).
u32 RentalGetFieldCount(void);                            // recruitable opponent count this battle
bool32 RentalRecruitLegal(u32 oppFieldIndex, u32 releaseSlot); // would this swap keep every rule?

// The recruit board (S4): pick one of the opponent's fielded mons and one of yours
// to release, with rule-breaking swaps blocked. Sets VAR_0x8006 (opp index),
// VAR_0x8004 (release slot) and VAR_RESULT (TRUE = recruit chosen, FALSE = skip) for
// the script's RentalDoRecruit. Defined in src/rental_recruit_screen.c; follow with
// `waitstate`.
void DoRentalRecruit(void);

// Put the run's bring count (3/4) into VAR_0x8005 for the party-select prompt.
void RentalSetBringCountVar(void);

// Leave standalone rental mode (soft reset to the title). The session is RAM-only.
void EndRentalMode(void);

// The draft screen itself (an adapted copy of the Battle Factory select screen),
// defined in src/rental_select_screen.c.
void DoRentalDraftScreen(void);

// The team-preview board (S3): shows both rosters as icons, scouts opponents, and
// takes the bring-N pick. Writes gSelectedOrderFromParty[] + gSpecialVar_Result the
// same way ChoosePartyForBattleFrontier does. Defined in src/rental_preview_screen.c.
// Call it from a map script followed by `waitstate`.
void DoRentalTeamPreview(void);

// Script special: begin a run (roll the offer) and launch the draft screen. Use it
// from a map script followed by `waitstate`, like the Factory's rent flow.
void StartRentalDraft(void);

#endif // GUARD_RENTAL_MODE_H
