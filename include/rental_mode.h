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
    u8 offerCount;
    u8 rosterCount;
    u8 format;         // enum RentalFormat
    u8 restrictedCap;  // 0 / 1 / 2 restricted-tier mons allowed
    u8 bringCount;     // 3 (singles) or 4 (doubles) brought per battle
};

extern struct RentalRun gRentalRun;

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

// The draft screen itself (an adapted copy of the Battle Factory select screen),
// defined in src/rental_select_screen.c.
void DoRentalDraftScreen(void);

// Script special: begin a run (roll the offer) and launch the draft screen. Use it
// from a map script followed by `waitstate`, like the Factory's rent flow.
void StartRentalDraft(void);

#endif // GUARD_RENTAL_MODE_H
