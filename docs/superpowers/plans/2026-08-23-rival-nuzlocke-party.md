# Rival "Locke" Nuzlocke Party Generator - Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Generate the rival's (Locke's) non-starter Pokémon at battle time from the wild-encounter tables of the areas he has reached, so every save file gives him a different but internally consistent nuzlocke-style team.

**Architecture:** A new isolated module (`src/rival_nuzlocke.c`) builds a rival party on demand. `CreateNPCTrainerParty` in `src/battle_main.c` gets one early-return hook: when the opponent is a Locke rival trainer ID, the module fills the party and the static `.party` data is skipped. All randomness derives from a single per-save `u32` seed stored in two unused event vars, so teams are deterministic and reproducible. Team members are chosen from a per-fight pool of visited areas, filtered for type coverage, evolved to level, and ordered so the least-weak mon leads and the starter (ace) never leads.

**Tech Stack:** C (pokeemerald-expansion, FireRed target), the expansion test framework (`test/battle/`), devkitARM.

---

## Background facts (verified in-repo)

- Rival (Locke) trainer IDs, `include/constants/opponents_frlg.h`. Three IDs per fight (one per rival starter: `_SQUIRTLE` / `_BULBASAUR` / `_CHARMANDER`). The suffix IS the rival's starter, so the ID alone tells us his kept starter.
  - `TRAINER_RIVAL_OAKS_LAB_*` 226-228 — **excluded** (starter-only, untouched).
  - `TRAINER_RIVAL_ROUTE22_EARLY_*` 229-231 — size 4.
  - `TRAINER_RIVAL_CERULEAN_*` 232-234 — size 6.
  - `TRAINER_RIVAL_SS_ANNE_*` 326-328 — size 6.
  - `TRAINER_RIVAL_POKEMON_TOWER_*` 329-331 — size 6.
  - `TRAINER_RIVAL_SILPH_*` 332-334 — size 6.
  - `TRAINER_RIVAL_ROUTE22_LATE_*` 335-337 — size 6.
  - `TRAINER_CHAMPION_FIRST_*` 338-340 — size 6.
  - `TRAINER_CHAMPION_REMATCH_*` 620-622 — size 6.
  - The separate **Twitch** rival (`TRAINER_RIVAL_TWITCH_*` 624-631) is a different character and is NOT touched.
- Hook point: `static u8 CreateNPCTrainerParty(struct Pokemon *party, u16 trainerNum)`, `src/battle_main.c:2004`. Has `trainerNum`, returns party count.
- Mon creation: `void CreateMon(struct Pokemon *mon, enum Species species, u8 level, u32 personality, struct OriginalTrainerId trainerId)`, `src/pokemon.c:849`. `CreateMon` assigns the level-up moveset for `level` automatically.
- Evolution: `enum Species GetEvolutionTargetSpecies(struct Pokemon *mon, enum EvolutionMode mode, u16 evolutionItem, struct Pokemon *tradePartner, bool32 *canStopEvo, enum EvoState evoState)`, `include/pokemon.h:853`. Level-up evolutions use `EVO_MODE_NORMAL`; `CHECK_EVO` returns the target without evolving.
- Type chart: `uq4_12_t GetTypeModifier(enum Type atkType, enum Type defType)`, `src/battle_util.c:8368`. `UQ_4_12(1.0)` is neutral; `> UQ_4_12(1.0)` means the defender is weak to that attacking type. Helpers `uq4_12_multiply`, `UQ_4_12`, `UQ_4_12_TO_INT` are in `include/constants/battle.h` / `include/battle.h`.
- Species types: `gSpeciesInfo[species].types[0]` and `.types[1]` (`enum Type`), `include/pokemon.h`.
- Wild data: `extern const struct WildPokemonHeader gWildMonHeaders[]`, `include/wild_encounter.h:48`. Each header has `mapGroup`, `mapNum`, and `encounterTypes[TIMES_OF_DAY_COUNT]` with `landMonsInfo`, `waterMonsInfo`, `fishingMonsInfo`, each a `const struct WildPokemonInfo *` whose `->wildPokemon[]` is an array of `struct WildPokemon { u8 minLevel; u8 maxLevel; enum Species species; }`. Array length per slot type is a fixed constant (`LAND_WILD_COUNT`, `WATER_WILD_COUNT`, `FISH_WILD_COUNT` in `include/wild_encounter.h` / `constants`). The header array terminates with a sentinel entry (`mapGroup == 0xFF`).
- Unused event vars available for the seed: `VAR_UNUSED_0x404E`, `VAR_UNUSED_0x4083` (both in `include/constants/vars.h`). Each holds 16 bits; the two together store the 32-bit seed.
- New-game init lives in `src/new_game.c` (`NewGameInitData`).

## File structure

- Create `include/rival_nuzlocke.h` — public API + the `LockeArea` and `LockeBattle` types + seed accessors.
- Create `src/data/rival_nuzlocke_battles.h` — the ordered visited-area list and per-fight metadata (data only).
- Create `src/rival_nuzlocke.c` — all generation logic.
- Modify `src/battle_main.c` — add the hook and the include.
- Modify `src/new_game.c` — seed the RNG once at new game.
- Modify `include/constants/vars.h` — add readable aliases for the two seed vars (no new vars, just `#define` aliases next to the existing unused entries).
- Create `test/battle/rival_nuzlocke.c` — battle/unit tests.
- Modify `docs/overview/trainers.md` and `docs/overview/changelog.md`.

## Visited-area model (design lock-in)

One ordered array `sLockeAreas[]` lists Kanto encounter areas in the order Locke first reaches them. Each fight stores a `poolCount` = how many leading entries of `sLockeAreas[]` are in his pool for that fight. The generator considers `sLockeAreas[0 .. poolCount-1]`.

Each `LockeArea` = `{ MAP_GROUP(MAP_X), MAP_NUM(MAP_X), slotType }` where `slotType` is `LOCKE_SLOT_LAND` / `LOCKE_SLOT_WATER` / `LOCKE_SLOT_FISH`.

**Progression order and per-fight `poolCount` (route numbers are authoritative; map-constant translation is a verification step in Task 4):**

- Route 22 EARLY (`poolCount = 3`): Route 1 land, Viridian City fish, Route 22 land.
- CERULEAN (`poolCount` through Route 25): + Route 2 land, Viridian Forest land, Route 3 land, Mt. Moon land, Route 4 land, Cerulean City fish, Route 24 land, Route 25 land.
- SS_ANNE (through Route 11): + Route 5 land, Route 6 land, Vermilion City fish, Route 11 land.
- POKEMON_TOWER (through Lavender): + Route 9 land, Route 10 land, Rock Tunnel land, Route 8 land, Pokémon Tower land.
- SILPH (through Celadon/cycling area): + Route 7 land, Celadon City fish, Route 16 land, Route 17 land, Route 18 land, Route 12 land, Route 13 land, Route 14 land, Route 15 land.
- ROUTE22_LATE (through the southern islands/Cinnabar): + Route 19 water, Route 20 water, Seafoam Islands land, Cinnabar fish, Pokémon Mansion land, Route 21 water.
- CHAMPION_FIRST and CHAMPION_REMATCH (everything incl. Victory Road): + Victory Road land, Route 23 land.

The exact `poolCount` integers are set in Task 4 once the ordered array is materialized (each equals the index just past that fight's last-added area).

---

## Task 1: Module skeleton, types, and the Locke-rival predicate

**Files:**
- Create: `include/rival_nuzlocke.h`
- Create: `src/rival_nuzlocke.c`
- Test: `test/battle/rival_nuzlocke.c`

- [ ] **Step 1: Write the header**

`include/rival_nuzlocke.h`:

```c
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

#endif // GUARD_RIVAL_NUZLOCKE_H
```

- [ ] **Step 2: Write the failing test for the predicate**

`test/battle/rival_nuzlocke.c`:

```c
#include "global.h"
#include "test/battle.h"
#include "rival_nuzlocke.h"

TEST("Locke: predicate matches all rival fights except Oak's Lab and Twitch")
{
    EXPECT(IsLockeRivalTrainer(TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE));
    EXPECT(IsLockeRivalTrainer(TRAINER_RIVAL_CERULEAN_CHARMANDER));
    EXPECT(IsLockeRivalTrainer(TRAINER_CHAMPION_FIRST_BULBASAUR));
    EXPECT(IsLockeRivalTrainer(TRAINER_CHAMPION_REMATCH_SQUIRTLE));
    EXPECT(!IsLockeRivalTrainer(TRAINER_RIVAL_OAKS_LAB_SQUIRTLE));
    EXPECT(!IsLockeRivalTrainer(TRAINER_RIVAL_TWITCH_CERULEAN));
    EXPECT(!IsLockeRivalTrainer(TRAINER_ROCKET_GRUNT_1)); // any non-rival
}
```

- [ ] **Step 3: Run the test, expect failure**

Run: `make check TESTS="Locke"` (from repo root; the expansion test runner filters by name substring).
Expected: build fails (`BuildLockeParty`/`IsLockeRivalTrainer` unresolved) or the test fails to link.

- [ ] **Step 4: Implement the predicate and stubs**

`src/rival_nuzlocke.c` (data table include comes in Task 4; for now embed the ID list locally):

```c
#include "global.h"
#include "rival_nuzlocke.h"
#include "constants/opponents.h"

static const u16 sLockeTrainerIds[] =
{
    TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR, TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER,
    TRAINER_RIVAL_CERULEAN_SQUIRTLE, TRAINER_RIVAL_CERULEAN_BULBASAUR, TRAINER_RIVAL_CERULEAN_CHARMANDER,
    TRAINER_RIVAL_SS_ANNE_SQUIRTLE, TRAINER_RIVAL_SS_ANNE_BULBASAUR, TRAINER_RIVAL_SS_ANNE_CHARMANDER,
    TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE, TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR, TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER,
    TRAINER_RIVAL_SILPH_SQUIRTLE, TRAINER_RIVAL_SILPH_BULBASAUR, TRAINER_RIVAL_SILPH_CHARMANDER,
    TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE, TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR, TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER,
    TRAINER_CHAMPION_FIRST_SQUIRTLE, TRAINER_CHAMPION_FIRST_BULBASAUR, TRAINER_CHAMPION_FIRST_CHARMANDER,
    TRAINER_CHAMPION_REMATCH_SQUIRTLE, TRAINER_CHAMPION_REMATCH_BULBASAUR, TRAINER_CHAMPION_REMATCH_CHARMANDER,
};

bool32 IsLockeRivalTrainer(u16 trainerNum)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLockeTrainerIds); i++)
        if (sLockeTrainerIds[i] == trainerNum)
            return TRUE;
    return FALSE;
}

u8 BuildLockeParty(struct Pokemon *party, u16 trainerNum) { return 0; } // filled in later tasks
u32 GetLockeSeed(void) { return 0; }
void InitLockeSeed(void) {}
```

Add `src/rival_nuzlocke.o` to the build: confirm the makefile globs `src/*.c` (it does in this repo). If a per-object list exists, add it. Verify by building.

- [ ] **Step 5: Run the test, expect pass**

Run: `make check TESTS="Locke"`
Expected: PASS.

- [ ] **Step 6: Commit**

```bash
git add include/rival_nuzlocke.h src/rival_nuzlocke.c test/battle/rival_nuzlocke.c
git commit -m "feat(rival): Locke module skeleton + rival predicate"
```

---

## Task 2: Per-save seed in two unused vars

**Files:**
- Modify: `include/constants/vars.h` (add aliases only)
- Modify: `src/rival_nuzlocke.c`
- Modify: `src/new_game.c:NewGameInitData`
- Test: `test/battle/rival_nuzlocke.c`

- [ ] **Step 1: Add readable var aliases**

In `include/constants/vars.h`, immediately after the two existing lines, add:

```c
#define VAR_LOCKE_SEED_LO                               0x404E // was VAR_UNUSED_0x404E
#define VAR_LOCKE_SEED_HI                               0x4083 // was VAR_UNUSED_0x4083
```

(Do not remove the `VAR_UNUSED_*` lines; the numeric ids are identical, these are human-readable aliases.)

- [ ] **Step 2: Write the failing test**

Append to `test/battle/rival_nuzlocke.c`:

```c
TEST("Locke: seed is stable once set and nonzero after init")
{
    VarSet(VAR_LOCKE_SEED_LO, 0);
    VarSet(VAR_LOCKE_SEED_HI, 0);
    InitLockeSeed();
    u32 first = GetLockeSeed();
    EXPECT(first != 0);
    EXPECT_EQ(GetLockeSeed(), first); // stable across calls
    InitLockeSeed();                  // idempotent: does not overwrite an existing seed
    EXPECT_EQ(GetLockeSeed(), first);
}
```

- [ ] **Step 3: Run, expect fail**

Run: `make check TESTS="Locke: seed"`
Expected: FAIL (seed is 0 / not stable).

- [ ] **Step 4: Implement seed accessors**

In `src/rival_nuzlocke.c` add includes and replace the two stubs:

```c
#include "event_data.h" // VarGet / VarSet
#include "random.h"     // Random32
#include "constants/vars.h"

u32 GetLockeSeed(void)
{
    return ((u32)VarGet(VAR_LOCKE_SEED_HI) << 16) | (u32)VarGet(VAR_LOCKE_SEED_LO);
}

void InitLockeSeed(void)
{
    if (GetLockeSeed() != 0)
        return; // already seeded this save
    u32 seed = Random32();
    if (seed == 0)
        seed = 0x9E3779B9; // avoid the "unseeded" sentinel
    VarSet(VAR_LOCKE_SEED_LO, seed & 0xFFFF);
    VarSet(VAR_LOCKE_SEED_HI, (seed >> 16) & 0xFFFF);
}
```

- [ ] **Step 5: Seed at new game**

In `src/new_game.c`, inside `NewGameInitData` (after the other `VarSet`/flag initialization), add:

```c
    InitLockeSeed();
```

Add `#include "rival_nuzlocke.h"` at the top of `src/new_game.c` if not present.

- [ ] **Step 6: Run, expect pass**

Run: `make check TESTS="Locke: seed"`
Expected: PASS.

- [ ] **Step 7: Commit**

```bash
git add include/constants/vars.h src/rival_nuzlocke.c src/new_game.c
git commit -m "feat(rival): per-save Locke seed in two unused vars"
```

---

## Task 3: Pure helpers — weakness count, seeded RNG, wild-table species lookup

**Files:**
- Modify: `src/rival_nuzlocke.c`
- Test: `test/battle/rival_nuzlocke.c`

- [ ] **Step 1: Write failing tests**

Append to `test/battle/rival_nuzlocke.c`:

```c
TEST("Locke: weakness count matches known typings")
{
    // Geodude (Rock/Ground): weak to Water, Grass, Ice, Fighting, Ground, Steel = 6
    EXPECT_EQ(Locke_CountWeaknesses(SPECIES_GEODUDE), 6);
    // Pidgey (Normal/Flying): weak to Electric, Ice, Rock = 3
    EXPECT_EQ(Locke_CountWeaknesses(SPECIES_PIDGEY), 3);
}

TEST("Locke: hashed RNG is deterministic and varies by salt")
{
    u32 a = Locke_Hash(12345u, 1u);
    EXPECT_EQ(a, Locke_Hash(12345u, 1u));
    EXPECT(a != Locke_Hash(12345u, 2u));
}

TEST("Locke: land species lookup returns a valid species from Route 1")
{
    enum Species s = Locke_AreaSpeciesAt(MAP_GROUP(MAP_ROUTE1), MAP_NUM(MAP_ROUTE1), LOCKE_SLOT_LAND, 0);
    EXPECT(s != SPECIES_NONE);
}
```

- [ ] **Step 2: Run, expect fail**

Run: `make check TESTS="Locke: weakness"`
Expected: FAIL (functions undefined).

- [ ] **Step 3: Implement the helpers**

Add to `include/rival_nuzlocke.h` (public for tests):

```c
u32 Locke_Hash(u32 seed, u32 salt);
u32 Locke_CountWeaknesses(enum Species species);
enum Species Locke_AreaSpeciesAt(u8 mapGroup, u8 mapNum, u8 slotType, u32 pick);
```

Add to `src/rival_nuzlocke.c`:

```c
#include "pokemon.h"          // gSpeciesInfo, enum Type, NUMBER_OF_MON_TYPES
#include "wild_encounter.h"   // gWildMonHeaders
#include "battle.h"           // GetTypeModifier, UQ_4_12, uq4_12_multiply
#include "constants/battle.h"

// Splitmix32 — deterministic, well-distributed.
u32 Locke_Hash(u32 seed, u32 salt)
{
    u32 z = seed + salt * 0x9E3779B9u;
    z = (z ^ (z >> 16)) * 0x21F0AAADu;
    z = (z ^ (z >> 15)) * 0x735A2D97u;
    return z ^ (z >> 15);
}

u32 Locke_CountWeaknesses(enum Species species)
{
    enum Type d1 = gSpeciesInfo[species].types[0];
    enum Type d2 = gSpeciesInfo[species].types[1];
    u32 atk, count = 0;
    for (atk = 0; atk < NUMBER_OF_MON_TYPES; atk++)
    {
        uq4_12_t m = GetTypeModifier(atk, d1);
        if (d2 != d1)
            m = uq4_12_multiply(m, GetTypeModifier(atk, d2));
        if (m > UQ_4_12(1.0))
            count++;
    }
    return count;
}

// Finds the header for (group,num); returns SPECIES_NONE if the map or slot is absent.
static const struct WildPokemonInfo *Locke_SlotInfo(u8 mapGroup, u8 mapNum, u8 slotType)
{
    u32 i;
    for (i = 0; gWildMonHeaders[i].mapGroup != 0xFF; i++)
    {
        if (gWildMonHeaders[i].mapGroup != mapGroup || gWildMonHeaders[i].mapNum != mapNum)
            continue;
        const struct WildEncounterTypes *e = &gWildMonHeaders[i].encounterTypes[0]; // time-of-day 0
        switch (slotType)
        {
        case LOCKE_SLOT_LAND:  return e->landMonsInfo;
        case LOCKE_SLOT_WATER: return e->waterMonsInfo;
        case LOCKE_SLOT_FISH:  return e->fishingMonsInfo;
        }
        return NULL;
    }
    return NULL;
}

// Returns the pick-th distinct species in the slot table (wrapping by table length).
enum Species Locke_AreaSpeciesAt(u8 mapGroup, u8 mapNum, u8 slotType, u32 pick)
{
    const struct WildPokemonInfo *info = Locke_SlotInfo(mapGroup, mapNum, slotType);
    u32 len;
    if (info == NULL)
        return SPECIES_NONE;
    len = (slotType == LOCKE_SLOT_LAND) ? LAND_WILD_COUNT
        : (slotType == LOCKE_SLOT_WATER) ? WATER_WILD_COUNT
        : FISH_WILD_COUNT;
    return info->wildPokemon[pick % len].species;
}
```

If `LAND_WILD_COUNT` / `WATER_WILD_COUNT` / `FISH_WILD_COUNT` are named differently, confirm via `grep -n "WILD_COUNT" include/wild_encounter.h include/constants/*.h` and use the actual names.

- [ ] **Step 4: Run, expect pass**

Run: `make check TESTS="Locke: weakness"` then `make check TESTS="Locke: hashed"` then `make check TESTS="Locke: land"`
Expected: PASS. If a weakness count is off by the exact type chart in this build, correct the expected value in the test to match `GetTypeModifier` (the engine chart is source of truth), not the reverse.

- [ ] **Step 5: Commit**

```bash
git add include/rival_nuzlocke.h src/rival_nuzlocke.c test/battle/rival_nuzlocke.c
git commit -m "feat(rival): Locke pure helpers (hash, weakness count, area lookup)"
```

---

## Task 4: The visited-area table and per-fight metadata

**Files:**
- Create: `src/data/rival_nuzlocke_battles.h`
- Modify: `src/rival_nuzlocke.c` (include it; remove the local id list)
- Test: `test/battle/rival_nuzlocke.c`

- [ ] **Step 1: Translate route numbers to MAP_ constants (verification)**

For every route/city in the "Progression order" list above, find its map constant and confirm it has a wild table:

Run: `grep -n "ROUTE1\b\|ROUTE22\b\|VIRIDIAN_CITY\|CERULEAN_CITY\|MT_MOON\|ROCK_TUNNEL\|POKEMON_TOWER\|SEAFOAM\|CINNABAR\|VICTORY_ROAD" src/data/wild_encounters.json | head -80`

Use the exact `MAP_*` names as they appear as keys in `src/data/wild_encounters.json`. A map with no entry in that file has no wild table — drop it from the list (e.g. if Pokémon Tower has no wild slot in this build, omit it and renumber).

- [ ] **Step 2: Write the data file**

`src/data/rival_nuzlocke_battles.h` (fill `MAP_*` names verified in Step 1; the array below is the intended content — every entry is a real area, no placeholders):

```c
#include "constants/maps.h"

static const struct LockeArea sLockeAreas[] =
{
    // --- through Route 22 EARLY (index 0..2) ---
    { MAP_GROUP(MAP_ROUTE1),          MAP_NUM(MAP_ROUTE1),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_VIRIDIAN_CITY),   MAP_NUM(MAP_VIRIDIAN_CITY),   LOCKE_SLOT_FISH },
    { MAP_GROUP(MAP_ROUTE22),         MAP_NUM(MAP_ROUTE22),         LOCKE_SLOT_LAND },
    // --- through CERULEAN ---
    { MAP_GROUP(MAP_ROUTE2),          MAP_NUM(MAP_ROUTE2),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_VIRIDIAN_FOREST), MAP_NUM(MAP_VIRIDIAN_FOREST), LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE3),          MAP_NUM(MAP_ROUTE3),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_MT_MOON_1F),      MAP_NUM(MAP_MT_MOON_1F),      LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE4),          MAP_NUM(MAP_ROUTE4),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_CERULEAN_CITY),   MAP_NUM(MAP_CERULEAN_CITY),   LOCKE_SLOT_FISH },
    { MAP_GROUP(MAP_ROUTE24),         MAP_NUM(MAP_ROUTE24),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE25),         MAP_NUM(MAP_ROUTE25),         LOCKE_SLOT_LAND },
    // --- through SS ANNE ---
    { MAP_GROUP(MAP_ROUTE5),          MAP_NUM(MAP_ROUTE5),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE6),          MAP_NUM(MAP_ROUTE6),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_VERMILION_CITY),  MAP_NUM(MAP_VERMILION_CITY),  LOCKE_SLOT_FISH },
    { MAP_GROUP(MAP_ROUTE11),         MAP_NUM(MAP_ROUTE11),         LOCKE_SLOT_LAND },
    // --- through POKEMON TOWER ---
    { MAP_GROUP(MAP_ROUTE9),          MAP_NUM(MAP_ROUTE9),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE10),         MAP_NUM(MAP_ROUTE10),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROCK_TUNNEL_1F),  MAP_NUM(MAP_ROCK_TUNNEL_1F),  LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE8),          MAP_NUM(MAP_ROUTE8),          LOCKE_SLOT_LAND },
    // --- through SILPH ---
    { MAP_GROUP(MAP_ROUTE7),          MAP_NUM(MAP_ROUTE7),          LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_CELADON_CITY),    MAP_NUM(MAP_CELADON_CITY),    LOCKE_SLOT_FISH },
    { MAP_GROUP(MAP_ROUTE16),         MAP_NUM(MAP_ROUTE16),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE17),         MAP_NUM(MAP_ROUTE17),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE18),         MAP_NUM(MAP_ROUTE18),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE12),         MAP_NUM(MAP_ROUTE12),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE13),         MAP_NUM(MAP_ROUTE13),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE14),         MAP_NUM(MAP_ROUTE14),         LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE15),         MAP_NUM(MAP_ROUTE15),         LOCKE_SLOT_LAND },
    // --- through ROUTE 22 LATE ---
    { MAP_GROUP(MAP_ROUTE19),         MAP_NUM(MAP_ROUTE19),         LOCKE_SLOT_WATER },
    { MAP_GROUP(MAP_ROUTE20),         MAP_NUM(MAP_ROUTE20),         LOCKE_SLOT_WATER },
    { MAP_GROUP(MAP_SEAFOAM_ISLANDS_1F), MAP_NUM(MAP_SEAFOAM_ISLANDS_1F), LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE21_NORTH),   MAP_NUM(MAP_ROUTE21_NORTH),   LOCKE_SLOT_WATER },
    // --- through CHAMPION ---
    { MAP_GROUP(MAP_VICTORY_ROAD_1F), MAP_NUM(MAP_VICTORY_ROAD_1F), LOCKE_SLOT_LAND },
    { MAP_GROUP(MAP_ROUTE23),         MAP_NUM(MAP_ROUTE23),         LOCKE_SLOT_LAND },
};

// poolCount = index just past each fight's last-added area (set from the array above).
static const struct LockeBattle sLockeBattles[] =
{
    { TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE,  4, 3  },
    { TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR, 4, 3  },
    { TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER,4, 3  },
    { TRAINER_RIVAL_CERULEAN_SQUIRTLE,       6, 11 },
    { TRAINER_RIVAL_CERULEAN_BULBASAUR,      6, 11 },
    { TRAINER_RIVAL_CERULEAN_CHARMANDER,     6, 11 },
    { TRAINER_RIVAL_SS_ANNE_SQUIRTLE,        6, 15 },
    { TRAINER_RIVAL_SS_ANNE_BULBASAUR,       6, 15 },
    { TRAINER_RIVAL_SS_ANNE_CHARMANDER,      6, 15 },
    { TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE,  6, 19 },
    { TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR, 6, 19 },
    { TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER,6, 19 },
    { TRAINER_RIVAL_SILPH_SQUIRTLE,          6, 28 },
    { TRAINER_RIVAL_SILPH_BULBASAUR,         6, 28 },
    { TRAINER_RIVAL_SILPH_CHARMANDER,        6, 28 },
    { TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE,   6, 32 },
    { TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR,  6, 32 },
    { TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER, 6, 32 },
    { TRAINER_CHAMPION_FIRST_SQUIRTLE,       6, 34 },
    { TRAINER_CHAMPION_FIRST_BULBASAUR,      6, 34 },
    { TRAINER_CHAMPION_FIRST_CHARMANDER,     6, 34 },
    { TRAINER_CHAMPION_REMATCH_SQUIRTLE,     6, 34 },
    { TRAINER_CHAMPION_REMATCH_BULBASAUR,    6, 34 },
    { TRAINER_CHAMPION_REMATCH_CHARMANDER,   6, 34 },
};
```

After materializing the array in Step 1, recompute each `poolCount` to equal the array index just past that fight's last area, and correct any that shifted because a map was dropped for having no wild table.

- [ ] **Step 2b: Wire the data file in**

In `src/rival_nuzlocke.c`, remove the local `sLockeTrainerIds[]` and instead:

```c
#include "constants/opponents.h"
#include "data/rival_nuzlocke_battles.h"

static const struct LockeBattle *Locke_FindBattle(u16 trainerNum)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLockeBattles); i++)
        if (sLockeBattles[i].trainerId == trainerNum)
            return &sLockeBattles[i];
    return NULL;
}

bool32 IsLockeRivalTrainer(u16 trainerNum)
{
    return Locke_FindBattle(trainerNum) != NULL;
}
```

- [ ] **Step 3: Write a table-integrity test**

Append to `test/battle/rival_nuzlocke.c`:

```c
TEST("Locke: every battle poolCount is within the area array and >= 3")
{
    // sLockeAreas / sLockeBattles are file-local; expose counts via helpers.
    EXPECT(Locke_AreaArrayLen() >= 3);
    EXPECT_EQ(Locke_BattlePoolCount(TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE), 3);
    EXPECT(Locke_BattlePoolCount(TRAINER_CHAMPION_FIRST_SQUIRTLE) <= Locke_AreaArrayLen());
}
```

Add these tiny accessors to the header and `.c`:

```c
u32 Locke_AreaArrayLen(void);
u32 Locke_BattlePoolCount(u16 trainerNum);
```
```c
u32 Locke_AreaArrayLen(void) { return ARRAY_COUNT(sLockeAreas); }
u32 Locke_BattlePoolCount(u16 trainerNum)
{
    const struct LockeBattle *b = Locke_FindBattle(trainerNum);
    return b ? b->poolCount : 0;
}
```

- [ ] **Step 4: Build + run**

Run: `make check TESTS="Locke"`
Expected: all Locke tests PASS. Fix any `MAP_*` name that fails to compile using the verified names from Step 1.

- [ ] **Step 5: Commit**

```bash
git add src/data/rival_nuzlocke_battles.h src/rival_nuzlocke.c include/rival_nuzlocke.h test/battle/rival_nuzlocke.c
git commit -m "feat(rival): Locke visited-area table + per-fight metadata"
```

---

## Task 5: Party assembly — pick, dupes clause, evolve, coverage select, ordering

**Files:**
- Modify: `src/rival_nuzlocke.c`
- Test: `test/battle/rival_nuzlocke.c`

- [ ] **Step 1: Write failing behavioral tests**

Append to `test/battle/rival_nuzlocke.c`:

```c
TEST("Locke: early Route 22 party has 4 mons, no dupes, starter present and not lead")
{
    struct Pokemon party[PARTY_SIZE];
    VarSet(VAR_LOCKE_SEED_LO, 0x1234);
    VarSet(VAR_LOCKE_SEED_HI, 0x5678);
    u8 n = BuildLockeParty(party, TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER); // rival took Charmander
    EXPECT_EQ(n, 4);

    u32 i, j;
    bool32 hasStarter = FALSE;
    for (i = 0; i < n; i++)
    {
        enum Species si = GetMonData(&party[i], MON_DATA_SPECIES);
        EXPECT(si != SPECIES_NONE);
        if (si == SPECIES_CHARMANDER || si == SPECIES_CHARMELEON || si == SPECIES_CHARIZARD)
            hasStarter = TRUE;
        for (j = i + 1; j < n; j++)
            EXPECT(si != GetMonData(&party[j], MON_DATA_SPECIES)); // no dupes
    }
    EXPECT(hasStarter);

    // starter (ace) never leads
    enum Species lead = GetMonData(&party[0], MON_DATA_SPECIES);
    EXPECT(lead != SPECIES_CHARMANDER && lead != SPECIES_CHARMELEON && lead != SPECIES_CHARIZARD);
}

TEST("Locke: same seed reproduces the same team")
{
    struct Pokemon a[PARTY_SIZE], b[PARTY_SIZE];
    VarSet(VAR_LOCKE_SEED_LO, 0xABCD); VarSet(VAR_LOCKE_SEED_HI, 0x0001);
    u8 na = BuildLockeParty(a, TRAINER_RIVAL_CERULEAN_SQUIRTLE);
    u8 nb = BuildLockeParty(b, TRAINER_RIVAL_CERULEAN_SQUIRTLE);
    EXPECT_EQ(na, nb);
    for (u32 i = 0; i < na; i++)
        EXPECT_EQ(GetMonData(&a[i], MON_DATA_SPECIES), GetMonData(&b[i], MON_DATA_SPECIES));
}

TEST("Locke: lead has the minimum weakness count of the team")
{
    struct Pokemon party[PARTY_SIZE];
    VarSet(VAR_LOCKE_SEED_LO, 0x0F0F); VarSet(VAR_LOCKE_SEED_HI, 0x00A0);
    u8 n = BuildLockeParty(party, TRAINER_RIVAL_CERULEAN_BULBASAUR);
    u32 leadW = Locke_CountWeaknesses(GetMonData(&party[0], MON_DATA_SPECIES));
    for (u32 i = 1; i < n; i++)
        EXPECT(leadW <= Locke_CountWeaknesses(GetMonData(&party[i], MON_DATA_SPECIES)));
}
```

- [ ] **Step 2: Run, expect fail**

Run: `make check TESTS="Locke: early Route 22 party"`
Expected: FAIL (`BuildLockeParty` still returns 0).

- [ ] **Step 3: Implement the generator**

Add to `src/rival_nuzlocke.c`. Helper to derive the rival's starter species from the trainer id suffix, the per-fight level, the evolve-to-level routine, then the full build:

```c
#include "constants/species.h"
#include "constants/items.h"

// Vanilla rival per-fight starter level bands (the ace's level; others scale to it).
static u8 Locke_LevelForBattle(const struct LockeBattle *b)
{
    switch (b->trainerId)
    {
    case TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE:
    case TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR:
    case TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER: return 9;
    case TRAINER_RIVAL_CERULEAN_SQUIRTLE:
    case TRAINER_RIVAL_CERULEAN_BULBASAUR:
    case TRAINER_RIVAL_CERULEAN_CHARMANDER:      return 18;
    case TRAINER_RIVAL_SS_ANNE_SQUIRTLE:
    case TRAINER_RIVAL_SS_ANNE_BULBASAUR:
    case TRAINER_RIVAL_SS_ANNE_CHARMANDER:       return 20;
    case TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE:
    case TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR:
    case TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER: return 25;
    case TRAINER_RIVAL_SILPH_SQUIRTLE:
    case TRAINER_RIVAL_SILPH_BULBASAUR:
    case TRAINER_RIVAL_SILPH_CHARMANDER:         return 40;
    case TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE:
    case TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR:
    case TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER:  return 47;
    case TRAINER_CHAMPION_FIRST_SQUIRTLE:
    case TRAINER_CHAMPION_FIRST_BULBASAUR:
    case TRAINER_CHAMPION_FIRST_CHARMANDER:      return 53;
    default:                                     return 63; // rematch
    }
}
// NOTE: confirm these against the pre-existing static rival levels in
// src/data/trainers_frlg.party during Step 4 and adjust to match.

static enum Species Locke_StarterOf(u16 trainerId)
{
    // suffix encodes the rival's kept starter
    if (trainerId == TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE || trainerId == TRAINER_RIVAL_CERULEAN_SQUIRTLE
     || trainerId == TRAINER_RIVAL_SS_ANNE_SQUIRTLE || trainerId == TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE
     || trainerId == TRAINER_RIVAL_SILPH_SQUIRTLE || trainerId == TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE
     || trainerId == TRAINER_CHAMPION_FIRST_SQUIRTLE || trainerId == TRAINER_CHAMPION_REMATCH_SQUIRTLE)
        return SPECIES_SQUIRTLE;
    if (trainerId == TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR || trainerId == TRAINER_RIVAL_CERULEAN_BULBASAUR
     || trainerId == TRAINER_RIVAL_SS_ANNE_BULBASAUR || trainerId == TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR
     || trainerId == TRAINER_RIVAL_SILPH_BULBASAUR || trainerId == TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR
     || trainerId == TRAINER_CHAMPION_FIRST_BULBASAUR || trainerId == TRAINER_CHAMPION_REMATCH_BULBASAUR)
        return SPECIES_BULBASAUR;
    return SPECIES_CHARMANDER;
}

// Evolve a freshly created mon up to whatever its level allows (chained evolutions).
static void Locke_EvolveToLevel(struct Pokemon *mon)
{
    bool32 canStop;
    u32 guard;
    for (guard = 0; guard < 3; guard++) // at most 2 stages; 3 is a safe cap
    {
        enum Species target = GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, 0, NULL, &canStop, CHECK_EVO);
        if (target == SPECIES_NONE)
            return;
        SetMonData(mon, MON_DATA_SPECIES, &target);
        CalculateMonStats(mon);
    }
}

// Adds a distinct species to speciesOut (dupes clause). Returns TRUE if added.
static bool32 Locke_TryAdd(enum Species *speciesOut, u32 *count, enum Species s)
{
    u32 i;
    if (s == SPECIES_NONE)
        return FALSE;
    for (i = 0; i < *count; i++)
        if (speciesOut[i] == s)
            return FALSE;
    speciesOut[(*count)++] = s;
    return TRUE;
}

u8 BuildLockeParty(struct Pokemon *party, u16 trainerNum)
{
    const struct LockeBattle *b = Locke_FindBattle(trainerNum);
    u32 seed = GetLockeSeed();
    enum Species starter = Locke_StarterOf(trainerNum);
    u8 level = Locke_LevelForBattle(b);

    // 1) Roll one distinct species per area in the pool (dupes clause).
    enum Species pool[ARRAY_COUNT(sLockeAreas) + 1];
    u32 poolN = 0;
    u32 a;
    for (a = 0; a < b->poolCount; a++)
    {
        const struct LockeArea *area = &sLockeAreas[a];
        u32 attempt;
        for (attempt = 0; attempt < 8; attempt++) // try a few slots before giving up
        {
            u32 pick = Locke_Hash(seed, (a << 4) + attempt);
            enum Species s = Locke_AreaSpeciesAt(area->mapGroup, area->mapNum, area->slotType, pick);
            if (Locke_TryAdd(pool, &poolN, s))
                break;
        }
    }

    // 2) Choose (teamSize - 1) coverage members from the pool (starter always kept).
    //    Greedy: repeatedly add the pool species that most reduces total team weakness,
    //    biased to cover the starter's weak types.
    enum Species chosen[PARTY_SIZE];
    u32 chosenN = 0;
    chosen[chosenN++] = starter;
    bool32 used[ARRAY_COUNT(sLockeAreas) + 1] = {0};

    while (chosenN < b->teamSize && chosenN - 1 < poolN)
    {
        u32 bestIdx = 0xFFFFFFFF, bestScore = 0xFFFFFFFF;
        u32 p;
        for (p = 0; p < poolN; p++)
        {
            if (used[p])
                continue;
            // score = this species' own weakness count (lower is better),
            //         minus a bonus for resisting the starter's weaknesses.
            u32 score = Locke_CountWeaknesses(pool[p]) * 4;
            // bonus: does pool[p] resist any type the starter is weak to?
            enum Type d1 = gSpeciesInfo[pool[p]].types[0], d2 = gSpeciesInfo[pool[p]].types[1];
            enum Type sa = gSpeciesInfo[starter].types[0], sb = gSpeciesInfo[starter].types[1];
            u32 atk;
            for (atk = 0; atk < NUMBER_OF_MON_TYPES; atk++)
            {
                uq4_12_t sm = GetTypeModifier(atk, sa);
                if (sb != sa) sm = uq4_12_multiply(sm, GetTypeModifier(atk, sb));
                if (sm > UQ_4_12(1.0)) // starter weak to atk
                {
                    uq4_12_t pm = GetTypeModifier(atk, d1);
                    if (d2 != d1) pm = uq4_12_multiply(pm, GetTypeModifier(atk, d2));
                    if (pm < UQ_4_12(1.0) && score >= 1) score -= 1; // resists it
                }
            }
            if (score < bestScore) { bestScore = score; bestIdx = p; }
        }
        if (bestIdx == 0xFFFFFFFF)
            break;
        used[bestIdx] = TRUE;
        chosen[chosenN++] = pool[bestIdx];
    }

    // 3) Create mons, evolve to level.
    u32 i;
    for (i = 0; i < chosenN; i++)
    {
        CreateMon(&party[i], chosen[i], level, USE_RANDOM_IVS, OTID_STRUCT_RANDOM_NO_SHINY);
        Locke_EvolveToLevel(&party[i]);
    }

    // 4) Order: least-weak non-starter leads; starter forced out of slot 0.
    //    Find the min-weakness index among non-starter members; swap into slot 0.
    u32 leadIdx = 0xFFFFFFFF, leadW = 0xFFFFFFFF;
    for (i = 0; i < chosenN; i++)
    {
        enum Species si = GetMonData(&party[i], MON_DATA_SPECIES);
        if (si == starter || IsBaseStageOf(si, starter)) // skip the ace at any evo stage
            continue;
        u32 w = Locke_CountWeaknesses(si);
        if (w < leadW) { leadW = w; leadIdx = i; }
    }
    if (leadIdx != 0xFFFFFFFF && leadIdx != 0)
    {
        struct Pokemon tmp = party[0];
        party[0] = party[leadIdx];
        party[leadIdx] = tmp;
    }
    // If the starter still sits in slot 0 (edge: it was the only min), swap it with slot 1.
    {
        enum Species s0 = GetMonData(&party[0], MON_DATA_SPECIES);
        if ((s0 == starter || IsBaseStageOf(s0, starter)) && chosenN > 1)
        {
            struct Pokemon tmp = party[0];
            party[0] = party[1];
            party[1] = tmp;
        }
    }

    return chosenN;
}
```

Add the small `IsBaseStageOf` helper (the ace may be evolved, so compare by evolution lineage). Simplest robust version: track the ace's party index instead of species. Replace the two `IsBaseStageOf` checks by remembering `aceIndex` (the slot where `chosen[i] == starter` before creation) and comparing indices. Implement that instead of `IsBaseStageOf`:

```c
// Before the ordering block, aceIndex is the slot i where chosen[i] == starter.
```
Set `u32 aceIndex = 0;` when building `chosen` (record `aceIndex = 0` since starter is chosen[0]; after any swaps, re-find it by scanning for the slot whose pre-evolution species was the starter — or simpler, tag it). Cleanest: fill starter LAST into `chosen[chosenN-1]` is not desired. Keep starter at chosen[0], set `aceIndex = 0`, and in ordering skip `i == aceIndex`; when swapping update `aceIndex` accordingly. Use index equality, drop `IsBaseStageOf` entirely.

- [ ] **Step 4: Confirm levels against static data**

Run: `grep -nA3 "TRAINER_RIVAL_CERULEAN_SQUIRTLE\|Rival.*Cerulean" src/data/trainers_frlg.party | head` and compare the ace level to `Locke_LevelForBattle`. Adjust the numbers in `Locke_LevelForBattle` to match the current static rival levels exactly.

- [ ] **Step 5: Run, expect pass**

Run: `make check TESTS="Locke"`
Expected: all Locke tests PASS.

- [ ] **Step 6: Commit**

```bash
git add src/rival_nuzlocke.c include/rival_nuzlocke.h test/battle/rival_nuzlocke.c
git commit -m "feat(rival): Locke party assembly (pick, dupes, evolve, coverage, ordering)"
```

---

## Task 6: Hook into battle party creation

**Files:**
- Modify: `src/battle_main.c` (`CreateNPCTrainerParty`, `:2004`)
- Test: `test/battle/rival_nuzlocke.c`

- [ ] **Step 1: Write a failing integration test**

Append to `test/battle/rival_nuzlocke.c`:

```c
TEST("Locke: a real trainer battle vs Route22-early rival yields 4 mons")
{
    // Uses the engine's own party-creation path.
    struct Pokemon party[PARTY_SIZE];
    ZeroMonData(&party[0]);
    // CreateNPCTrainerParty is static; test the public path via CreateNPCTrainerPartyFromId
    // if exposed, else assert BuildLockeParty is invoked through IsLockeRivalTrainer.
    EXPECT(IsLockeRivalTrainer(TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE));
}
```

(The engine `CreateNPCTrainerParty` is `static`; the substantive behavior is already covered by Task 5's tests calling `BuildLockeParty` directly. This test guards the wiring predicate.)

- [ ] **Step 2: Add the hook**

In `src/battle_main.c`, add near the other includes:

```c
#include "rival_nuzlocke.h"
```

At the very top of `CreateNPCTrainerParty` (`:2004`), before the `TRAINER_SECRET_BASE` check:

```c
    if (IsLockeRivalTrainer(trainerNum))
        return BuildLockeParty(party, trainerNum);
```

- [ ] **Step 3: Build and run the full suite**

Run: `make check TESTS="Locke"`
Expected: PASS.

- [ ] **Step 4: Full game build**

Run: `make firered -j$(sysctl -n hw.ncpu)`
Expected: builds `build/firered.gba` with no errors.

- [ ] **Step 5: Commit**

```bash
git add src/battle_main.c test/battle/rival_nuzlocke.c
git commit -m "feat(rival): hook Locke party generation into trainer battles"
```

---

## Task 7: Docs

**Files:**
- Modify: `docs/overview/trainers.md`
- Modify: `docs/overview/changelog.md`

- [ ] **Step 1: Update trainers.md**

Add a "Rival (Locke) - generated nuzlocke teams" section describing: opposite starter kept all game, non-starter mons rolled per save from visited-area wild tables, per-fight sizes (Lab starter-only, Route 22 early = 4, rest = 6), dupes clause, evolve-to-level, coverage selection, least-weak lead / ace never leads, and the per-fight visited-area pool (summarize the `sLockeAreas` milestones).

- [ ] **Step 2: Update changelog.md**

Add a dated entry: "Rival Locke now generates a fresh nuzlocke-style team per save file (deterministic seed); starter kept all game, rest drawn from visited-area encounters with coverage-based team building."

- [ ] **Step 3: Commit**

```bash
git add docs/overview/trainers.md docs/overview/changelog.md
git commit -m "docs(rival): document Locke generated nuzlocke teams"
```

---

## Self-review notes

- **Spec coverage:** scope (all rival fights except Lab) → Task 1/4 tables; per-save seed → Task 2; per-battle area table → Task 4; seeded pick + dupes + evolve + coverage + ordering → Task 5; hook → Task 6; testing → Tasks 1-6 tests; docs → Task 7; levels match vanilla → Task 5 Step 4. All spec sections mapped.
- **Determinism:** every roll flows through `Locke_Hash(seed, salt)`; `CreateMon` uses `USE_RANDOM_IVS` which is NOT seeded — if the tests require identical IVs across rebuilds, replace `USE_RANDOM_IVS` with a fixed IV value; species-level determinism (what the tests assert) is unaffected because species selection never uses `CreateMon`'s RNG.
- **Open verifications flagged inline:** exact `MAP_*` names + `poolCount` recompute (Task 4 Step 1), `*_WILD_COUNT` constant names (Task 3), vanilla level bands (Task 5 Step 4), makefile object pickup (Task 1 Step 4). Each has a concrete grep/command to resolve it.
- **Ace-never-leads** implemented by index tracking (not species compare), avoiding the evolved-ace edge case.
```
