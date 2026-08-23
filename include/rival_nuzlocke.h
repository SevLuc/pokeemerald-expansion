#ifndef GUARD_RIVAL_NUZLOCKE_H
#define GUARD_RIVAL_NUZLOCKE_H

#include "global.h"

enum LockeSlotType
{
    LOCKE_SLOT_LAND,
    LOCKE_SLOT_WATER,
    LOCKE_SLOT_FISH,
};

struct LockeArea
{
    u8 mapGroup;
    u8 mapNum;
    u8 slotType; // enum LockeSlotType
};

struct LockeBattle
{
    u16 trainerId;   // any one of the three starter variants
    u8 teamSize;     // total mons incl. starter
    u8 poolCount;    // number of leading sLockeAreas[] entries in this fight's pool
};

// Returns TRUE if trainerNum is a Locke (non-Twitch) rival fight that
// should use runtime generation (all rival fights except Oak's Lab).
bool32 IsLockeRivalTrainer(u16 trainerNum);

// Fills party with Locke's generated team, returns the count.
u8 BuildLockeParty(struct Pokemon *party, u16 trainerNum);

// Per-save seed, stored across two unused vars.
u32 GetLockeSeed(void);
void InitLockeSeed(void);

// Pure helpers (deterministic, no global state).
u32 Locke_Hash(u32 seed, u32 salt);
u32 Locke_CountWeaknesses(enum Species species);
enum Species Locke_AreaSpeciesAt(u8 mapGroup, u8 mapNum, u8 slotType, u32 pick);

#endif // GUARD_RIVAL_NUZLOCKE_H
