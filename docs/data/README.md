# Pokémon dataset (for team-building)

Generated from **this build's own source**, so any team you build from it is
guaranteed to work in-game (no move a species can't actually learn here).
Covers the full National Dex through Gen 9 as shipped by pokeemerald-expansion.

Regenerate after pulling RHH (data can change):

```bash
python3 docs/data/build_dex.py
```

## Files

### `pokedex-index.json` — the filter list (~125 KB)
Compact. Load this into Claude to narrow the roster. Keyed by species constant:

```json
"CHARIZARD": { "gen": 1, "types": ["FIRE", "FLYING"], "hasMovepool": true }
```

- `gen` — generation the species was introduced (1-9).
- `types` — one entry = mono-type. Reflects this build's config
  (Fairy on: `P_UPDATED_TYPES = GEN_LATEST`, so Clefairy = Fairy, etc.).
- `hasMovepool` — `true` if the species has its own entry in `movepools.json`.
- `baseFormAlias` (optional) — species that exist only as forms in source
  (e.g. `GASTRODON` -> `GASTRODON_WEST`); type/gen borrowed from that form.
- `typesFromExpansionMacro` (optional) — types hardcoded for macro-defined
  species the parser can't read (Unown, Arceus, Silvally, Genesect, Florges,
  Flabébé, Vivillon, Minior, Mothim, Furfrou, Alcremie, Ogerpon, Spewpa,
  Scatterbug). Base-form typing.

### `movepools.json` — the movesets (~1.9 MB)
Copy of `src/data/pokemon/all_learnables.json`. Every species mapped to its
**full learnable pool** (level-up + TM + egg + tutor, already merged). Pull
moves only for your finalists so Claude's context stays light.

```json
"ARCHALUDON": ["MOVE_AURA_SPHERE", "MOVE_BODY_PRESS", "MOVE_DRACO_METEOR", ...]
```

## Counts

- **1387** index entries total.
- **1110** are buildable (`hasMovepool: true`) — the real roster to pick from.
- **277** are Mega / Gmax / cosmetic / totem forms with no own movepool
  (they inherit their base form's). Filter these out with `hasMovepool`.
  Note: Mega / Z / Dynamax / Tera are OFF in this hack anyway.

Per generation (index entries incl. forms):
`{1:279, 2:114, 3:175, 4:101, 5:194, 6:98, 7:116, 8:122, 9:130}`

## Suggested workflow

1. Give Claude `pokedex-index.json`. Filter by gen / type / `hasMovepool`,
   plus whatever Kanto-authentic rules you want.
2. Shortlist species.
3. Pull those keys from `movepools.json` to pick fun, legal movesets.
4. Write teams in Pokémon Showdown syntax in `src/data/trainers.party`.
