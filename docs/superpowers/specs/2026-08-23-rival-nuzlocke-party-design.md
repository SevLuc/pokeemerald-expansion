# Rival "Locke" Nuzlocke Party Generator - Design

Date: 2026-08-23
Status: Approved (design), pending implementation plan

## Concept

The rival is reflavored as **Locke**, a trainer who plays the game in a
nuzlocke style: he keeps his starter for the whole game and fills the rest of
his team from wild encounters in the areas he has "visited" so far. Because his
non-starter mons are rolled per save, **every playthrough gives Locke a
different team**, while any single run stays internally consistent.

- Starter: the type that counters the player's starter (vanilla rival behavior).
  Kept the entire game, always on the team, but never led with.
- Everything else: generated at runtime from the wild encounter tables of the
  areas Locke has reached by that point in the story.

## Scope

- Applies to **all rival battles except Oak's Lab**. The Lab fight is
  starter-only in vanilla (level ~5, no wilds caught yet), so it keeps its
  existing static data and is untouched.
- Route 22 (early) = **4 mons** (starter + Route 1 + Viridian + Route 22).
- Every rival fight from Cerulean onward = **6 mons** (starter + 5).

## Persistence

- A single `u32` seed per save file, generated once at new game.
- Stored in two free 16-bit event vars (hi/lo) to avoid editing the SaveBlock
  struct, so existing saves stay compatible.
- Every rival team is derived **deterministically** from
  `seed + that fight's visited-area list + the wild encounter tables`.
- Consequences: reload / blackout-and-retry yields the **same** team within a
  run; a new save yields a different run. No team data is stored beyond the seed.

## Data

### Per-battle metadata table

`{ trainerId, teamSize, [visited areas] }` for each Locke fight (excluding the
Lab). Each "area" is a wild encounter source: a map + slot type (grass / water).

- Route 22 (early): size 4, areas = [Route 1 grass, Viridian City water,
  Route 22 grass].
  - Viridian water is legal from game start in this build: the Viridian
    Fisherman NPC gifts a Super Rod ungated, and all rods roll super-rod slots
    (see commit 285a2b8ff4, `data/maps/ViridianCity_Frlg`).
- All later fights: size 6, area list = every catchable area reachable by that
  story beat.
- The full visited-area list per fight is derived from FRLG progression during
  planning. This is real, careful work and is the backbone of the feature.

### Species source

Existing `gWildMonHeaders` (grass and water/fishing slots per map). No new
species data is authored.

## Generation algorithm (per fight)

1. Look up battle meta: team size `N`, ordered visited-area list.
2. Determine **starter**: read the opposite-type starter var (the type that
   counters the player's choice). Player starters are already rolled per save in
   `VAR_STARTER_GRASS/WATER/FIRE` (`src/starter_choose.c`). Starter is always on
   the team.
3. For each visited area, make a **seeded pick** of one species from that area's
   wild table, using a stable hash of `seed + area identity`.
   - **Dupes clause**: if the picked species is already on the team, advance to
     the next candidate slot in that table until a new species is found. If an
     area genuinely cannot yield a new species (tiny table), allow a duplicate as
     a last-resort fallback.
4. **Evolve** each picked species to the highest evolution stage its level
   allows for this fight (a Route 1 Pidgey rolled early is a Pidgeotto/Pidgeot by
   the Champion fight).
5. Build the **candidate pool** = starter + all area picks.
6. **Slot fill when pool > N** (coverage-driven, not recency):
   - Starter is always kept.
   - Greedily choose the other `N-1` members to:
     a. prioritize mons that resist the types the starter is weak to,
     b. then minimize shared weaknesses across the whole team,
     c. maximize versatility so there is always a clean defensive switch-in.
   - Uses the engine type-effectiveness chart.
7. **Ordering**:
   - Lead (slot 0) = the team member with the **fewest** type weaknesses (best
     defensive pivot).
   - The starter (Locke's ace) is **never** in slot 0.
8. **Levels**: match the vanilla rival's per-fight level band (preserves the
   difficulty curve). Generate each mon with its level-appropriate level-up
   moveset and solid IVs.

All steps are deterministic given the seed, so a run is reproducible and the
generator is unit-testable.

## Code structure

- New module `src/rival_nuzlocke.c` + `include/rival_nuzlocke.h`. All logic
  isolated here.
  - Public entry: `u8 BuildLockeParty(struct Pokemon *party, u16 trainerId)`,
    returns the party count.
  - Internal helpers: seeded area pick, dupes check, evolve-to-level, coverage
    selection, lead ordering.
- One hook in `CreateNPCTrainerPartyFromTrainer`
  (`src/battle_main.c:1864`): when the trainer is a Locke rival ID, call
  `BuildLockeParty` and return its count, bypassing the static `.party` read for
  that fight.
- Static rival teams in `src/data/trainers_frlg.party` remain as an untouched
  fallback (never read while the hook is active).

## Testing

- Battle test in `test/battle/` (required for new mechanics). With a fixed seed
  and a fixed player starter choice, assert:
  - correct team size per fight (4 for early Route 22, 6 later),
  - no duplicate species (dupes clause holds),
  - starter is present and is **not** in slot 0,
  - lead (slot 0) has the minimal weakness count of the team.

## Docs to update in the same PR

- `docs/overview/trainers.md` (describe Locke's generated teams / per-fight
  area pools).
- `docs/overview/changelog.md`.

## Open items resolved

- Levels: match vanilla rival per-fight levels (default, approved).
- No simulated deaths: team is cumulative (pool only grows); losses are not
  modeled. Chosen for fair, tunable difficulty.

## Non-goals

- No new sprites, tilesets, maps, or music (text/data/logic only).
- No change to the player's own nuzlocke options (no forced clauses on the
  player; "fair" per project direction).
- No battle-engine refactor.
