# Design: Per-save randomized starters

Date: 2026-08-22
Status: approved (pending spec review)

## Goal

Give the player a different starter trio on every playthrough. The three
choices are always one Grass, one Water, and one Fire starter, but the SPECIES
filling each slot is randomized per save, drawn independently from all nine
generations of starters. The player still chooses by type at Oak's lab exactly
as in vanilla FireRed.

## Behavior

- On a new save, the game rolls three species: one random Grass starter, one
  random Water starter, one random Fire starter. Each type rolls its generation
  independently (a run can be Gen 5 Grass + Gen 1 Water + Gen 3 Fire).
- The roll happens once per save and is then stable: re-entering Oak's lab, or
  reloading, never re-rolls.
- The three Poke Balls in Oak's lab show and give the rolled species. Examining
  a ball shows that species' front sprite; taking it gives that species at
  level 5.
- The player still picks by type/slot. Which slot maps to which type is
  unchanged from vanilla.
- The rival is NOT changed. The rival keeps its own starter handling
  (`RIVAL_STARTER_SPECIES` and the rival battle trainers are untouched).

## Starter pools (all 9 generations, 27 species)

Order below is Gen 1 through Gen 9. Species constants to be verified against the
build at implementation time.

- Grass: Bulbasaur, Chikorita, Treecko, Turtwig, Snivy, Chespin, Rowlet,
  Grookey, Sprigatito
- Water: Squirtle, Totodile, Mudkip, Piplup, Oshawott, Froakie, Popplio,
  Sobble, Quaxly
- Fire: Charmander, Cyndaquil, Torchic, Chimchar, Tepig, Fennekin, Litten,
  Scorbunny, Fuecoco

## How starters currently work (baseline, verified on disk)

- FRLG uses the three-Poke-Ball table in
  `data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc` (NOT the RSE rotating
  `starter_choose.c` screen; `sStarterMon` there is unused in FRLG).
- Each ball script hardcodes the species, for example:
  - `setvar PLAYER_STARTER_NUM, 0` / `setvar PLAYER_STARTER_SPECIES, SPECIES_BULBASAUR` / `setvar RIVAL_STARTER_SPECIES, SPECIES_CHARMANDER`
  - Squirtle ball: NUM 1, PLAYER Squirtle, RIVAL Bulbasaur
  - Charmander ball: NUM 2, PLAYER Charmander, RIVAL Squirtle
- `PLAYER_STARTER_NUM` is `VAR_TEMP_1`, `PLAYER_STARTER_SPECIES` is `VAR_TEMP_2`
  (aliased at the top of that scripts.inc).
- The ball flow then does `showmonpic PLAYER_STARTER_SPECIES`,
  `givemon PLAYER_STARTER_SPECIES, 5`, `copyvar VAR_STARTER_MON, PLAYER_STARTER_NUM`,
  `bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES`.
- `VAR_STARTER_MON` (the chosen slot 0/1/2) drives all downstream type-based
  scripts (rival battles at Route 22, Cerulean, Pokemon Tower, etc.). It stays
  meaningful because the player still picks a type slot.

## Components

### 1. Species tables + roll special (C)

Add to `src/field_specials.c` (or a small dedicated file if cleaner):

- Three `static const u16` tables, 9 entries each, in generation order:
  `sGrassStarters[9]`, `sWaterStarters[9]`, `sFireStarters[9]`.
- A special `RollRandomStarters(void)`:
  - If the grass starter var is already set (non-zero), return without changing
    anything (idempotent; guarantees one roll per save).
  - Otherwise pick three independent random indices in 0..8 (using the game's
    `Random()` helper) and write the corresponding species into the three saved
    vars via `VarSet`.
- Register it in `data/specials.inc` with `def_special RollRandomStarters`.
- Extend `GetStarterPokemon(slot)` (same file) to be rolled-aware: when the roll
  has happened (grass var non-zero), return the rolled species for the slot
  (0 = Grass, 1 = Water, 2 = Fire, matching `PLAYER_STARTER_NUM` /
  `VAR_STARTER_MON`); otherwise fall back to the original `sStarterMon` lookup.
  This keeps the FRLG consumers that call `GetStarterPokemon(VAR_STARTER_MON)`
  correct without extra script changes: the credits reel (`src/credits.c`) and
  the Champion's Room congratulations text
  (`PokemonLeague_ChampionsRoom_Frlg`) name the rolled species. The RSE rotating
  selection screen also routes through this function but is unused in FRLG.

### 2. Saved vars

Alias three currently-unused saved vars in `include/constants/vars.h` (from the
Hoenn/unused pool, which never fires in FRLG), for example:

- `VAR_STARTER_GRASS`
- `VAR_STARTER_WATER`
- `VAR_STARTER_FIRE`

Exact 0x40xx addresses to be picked at implementation from confirmed-unused
entries, and documented in the vars.h comment.

### 3. Roll hook (script)

In `PalletTown_ProfessorOaksLab_Frlg/scripts.inc`, call
`special RollRandomStarters` once at the start of the starter scene, before the
balls become interactable (the scene setup that already runs when the player is
first allowed to approach the table). The special's own guard makes a duplicate
call harmless.

### 4. Ball script edits (script)

In the same scripts.inc, in each of the three ball-selection blocks, replace the
hardcoded species line:

- Grass ball: `setvar PLAYER_STARTER_SPECIES, SPECIES_BULBASAUR`
  becomes `copyvar PLAYER_STARTER_SPECIES, VAR_STARTER_GRASS`
- Water ball: `setvar PLAYER_STARTER_SPECIES, SPECIES_SQUIRTLE`
  becomes `copyvar PLAYER_STARTER_SPECIES, VAR_STARTER_WATER`
- Fire ball: `setvar PLAYER_STARTER_SPECIES, SPECIES_CHARMANDER`
  becomes `copyvar PLAYER_STARTER_SPECIES, VAR_STARTER_FIRE`

Everything else in those blocks stays: `PLAYER_STARTER_NUM`,
`RIVAL_STARTER_SPECIES`, `showmonpic`, `givemon`, `bufferspeciesname`,
`copyvar VAR_STARTER_MON, PLAYER_STARTER_NUM`. Because the downstream commands
read `PLAYER_STARTER_SPECIES`, they now show/give the rolled species with no
further change.

## Data flow

new save -> (first lab starter scene) special RollRandomStarters -> writes
VAR_STARTER_GRASS/WATER/FIRE (once) -> player examines a ball -> that ball's
block copies the matching VAR_STARTER_* into PLAYER_STARTER_SPECIES -> showmonpic
/ givemon use it -> VAR_STARTER_MON set to the slot -> rest of game unchanged.

## Left unchanged (explicit)

- Rival: `RIVAL_STARTER_SPECIES` and all rival battle trainers. Per direction,
  the rival has its own starter already.
- `VAR_STARTER_MON` semantics (still the chosen slot 0/1/2).
- The RSE `sStarterMon` / `starter_choose.c` path (unused in FRLG).
- Slot-to-type mapping and ball object placement.

## Testing

- Debug menu (already enabled in non-release builds): start several new games,
  confirm the three balls show different species across runs and that the three
  types are respected.
- For a given save, confirm re-entering the lab does not re-roll.
- Pick each of the three balls in separate runs; confirm the received level-5
  mon is the rolled species and its Pokedex "seen/own" is set.
- Confirm rival battles still function (rival species unchanged).
- No battle test is added: no new move or ability is introduced.

## Risks and mitigations

- Species constant names: verify all 27 exist in this build (Gen 9 families are
  present) before writing the tables.
- Idempotent roll: the guard keys off the vars being non-zero; species IDs are
  always non-zero, so a valid roll is distinguishable from unset (0).
- Save compatibility: only relevant for new saves; existing saves that already
  picked a starter are unaffected (they never call the roll again, and the balls
  are already consumed).
- Var choice: pick vars confirmed unused in FRLG to avoid clobbering state.

## Out of scope (YAGNI)

- Re-roll / reset option.
- Matched-generation mode (rejected in favor of independent-per-slot).
- Randomizing the rival.
- Any change to starter movesets, levels, or evolutions.
