#ifndef GUARD_BATTLE_TOWER_RENTAL_H
#define GUARD_BATTLE_TOWER_RENTAL_H

#include "data.h" // struct TrainerMon

// Rental pool for the standalone rental battle mode (see
// docs/battle-tower/phase-1-implementation-plan.md).
//
// The data table gRentalMons[] is GENERATED from docs/battle-tower/movesets/*.json
// by tools/gen_rental_mons.py into src/data/battle_tower/rental_mons.h. Each set in
// the library becomes one rentable entry (a struct TrainerMon), so a "rental" is a
// specific build (species + moves + item + ability + nature + EVs + IVs), not just a
// species. CreateFacilityMon() turns an entry into a live battle Pokemon.
//
// Entries are grouped by tier and, within a tier, kept in library order. All of the
// restricted tiers are contiguous at the end (>= RENTAL_TIER_FIRST_RESTRICTED) so the
// per-format restricted cap (0 / 1 / 2) is a single comparison.

enum RentalTier
{
    RENTAL_TIER_STANDARD,               // fully-evolved, any generation
    RENTAL_TIER_REGIONAL,               // Alolan / Galarian / Hisuian / Paldean finals
    RENTAL_TIER_ALTFORME,               // alternate battle formes (Rotom, Oricorio, ...)
    RENTAL_TIER_EVIOLITE,               // curated Eviolite NFE picks
    RENTAL_TIER_MEGA,                   // standard-based Mega Evolutions (not restricted)
    // Everything from here down counts against the restricted cap.
    RENTAL_TIER_RESTRICTED_LEGENDARY,
    RENTAL_TIER_SUB_LEGENDARY,
    RENTAL_TIER_MYTHICAL,
    RENTAL_TIER_PARADOX,
    RENTAL_TIER_ULTRA_BEAST,
    RENTAL_TIER_MEGA_RESTRICTED,        // legendary-based Mega Evolutions
    RENTAL_TIER_COUNT
};

#define RENTAL_TIER_FIRST_RESTRICTED RENTAL_TIER_RESTRICTED_LEGENDARY

// Total number of rentable sets. Kept in sync with the generated table by
// tools/gen_rental_mons.py, which errors out if the counts diverge.
#define NUM_RENTAL_MONS 6229

// [start, start + count) slice of gRentalMons[] for one tier.
struct RentalTierRange
{
    u16 start;
    u16 count;
};

extern const struct TrainerMon gRentalMons[NUM_RENTAL_MONS];
extern const u8 gRentalMonTier[NUM_RENTAL_MONS];
extern const struct RentalTierRange gRentalTierRanges[RENTAL_TIER_COUNT];

static inline bool32 IsRentalTierRestricted(u32 tier)
{
    return tier >= RENTAL_TIER_FIRST_RESTRICTED;
}

#endif // GUARD_BATTLE_TOWER_RENTAL_H
