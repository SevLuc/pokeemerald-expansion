---
name: moveset-legality
description: >-
  Produce a full moveset-legality overview for a single Pokemon at a level cap,
  using THIS build's own data. Reports the legal move pool (level-up <= cap, egg,
  TM, tutor/other), the moves locked out by the cap, and every advised set from
  docs/data/trainer-movesets.json with per-move legal/illegal verdicts and the
  reason for each. Use when building or vetting a trainer/gym pool and you need to
  know which moves a species can legally have at a capped level. Trigger on
  requests like "is this moveset legal for X at level N", "what can X learn by
  level 14", "check the advised sets for X", or building trainer teams under a
  level cap.
---

# Moveset legality overview (per Pokemon, at a level cap)

Runs one deterministic report per species. All facts come from the repository's
own data, so any move it marks LEGAL is actually learnable in this build.

## Run it

```bash
python3 .claude/skills/moveset-legality/check_moveset.py SPECIES [LEVEL_CAP]
```

- `SPECIES` — species constant without the `SPECIES_` prefix, uppercase.
  Regional/other forms use their form suffix: `ONIX`, `GEODUDE_ALOLA`,
  `GROWLITHE_HISUI`, `AERODACTYL`, `CHEWTLE`, `STAKATAKA`.
- `LEVEL_CAP` — integer, default `14`.

## What it prints

1. **Header** — species, the level cap, the configured level-up learnset
   generation (read from `P_LVL_UP_LEARNSETS`; `GEN_LATEST` is resolved to the
   number in `include/config/general.h`), the species' **abilities** (the slot-3
   ability is marked `(hidden)`), and its **gender** ratio (so you can tell
   whether a trainer mon can be female / is genderless).
2. **Legal pool at cap**, split into four buckets:
   - **Level-up (<= cap)** with the level each move is learned.
   - **Egg moves.**
   - **TM moves** the species can learn (this build's TM list in
     `include/constants/tms_hms.h`, intersected with the species pool).
   - **Tutor / other teachable moves** — everything else in the species'
     full legal pool that is not a level-up move at any level and not an egg move.
3. **Locked by cap** — level-up moves learned ABOVE the cap that have no TM,
   tutor, or egg path (these are the only moves the cap actually removes).
4. **Advised sets** — every entry for the species in
   `docs/data/trainer-movesets.json` (sets used by established hard romhacks),
   each move tagged LEGAL/ILLEGAL with the reason (level-up L#, egg, TM, tutor,
   or "> cap, no TM/tutor/egg path").

## Legality model

A move is LEGAL for a trainer Pokemon at the cap if it is any of:
- a level-up move learned at or below the cap, **or**
- an egg move, **or**
- a TM move the species can learn, **or**
- a tutor / other teachable move in the species' full pool.

A move is ILLEGAL only when its sole source is a level-up move learned above the
cap. TM/tutor/egg moves are never level-gated for trainer Pokemon.

## Data sources

| File | Provides |
|------|----------|
| `include/config/pokemon.h` | configured level-up learnset gen |
| `include/config/general.h` | `GEN_LATEST` value |
| `src/data/pokemon/level_up_learnsets/gen_N.h` | level-up moves + levels |
| `src/data/pokemon/egg_moves.h` | egg moves |
| `include/constants/tms_hms.h` | this build's TM/HM list |
| `src/data/pokemon/all_learnables.json` | full legal pool (level-up+egg+TM+tutor) |
| `docs/data/trainer-movesets.json` | advised sets from other romhacks |

`trainer-movesets.json` and `all_learnables.json` are read from the working tree,
falling back to `origin/master` if a file is not present on the current branch.

## Notes

- Run from the repository root.
- If the level cap changes, pass the new value; nothing is hardcoded to 14.
- The report gives data only, no recommendations. Pick moves from the buckets.
