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

---

# Trainer movesets (reference, from other hard-mode hacks)

`trainer-movesets.json` is a **species-keyed reference** of how three
respected hard-but-fair romhacks actually build each Pokémon on trainers.
Use it for inspiration when building our teams: ask "what are good movesets
for Onix?" and pull `trainer-movesets.json["ONIX"]` to see every set those
hacks give Onix (item, ability, nature, moves, level, which trainer).

These are **external references, not our data.** Some sets use megas,
Gen 8/9 moves, or abilities that are OFF or out-of-era here. Treat them as
ideas; always confirm legality against `movepools.json` before writing a
team in `src/data/trainers.party`.

### Sources

| `source` value        | Hack           | Notes |
|-----------------------|----------------|-------|
| `Run&Bun`             | Run & Bun      | full sets: item/ability/nature/moves |
| `PlatinumKaizo`       | Platinum Kaizo | item/ability/nature/moves + AI flags in source |
| `EmeraldKaizo`        | Emerald Kaizo  | from EK Mastersheet.txt |
| `EmeraldKaizo-Rival`  | Emerald Kaizo  | rival teams (vary by player starter) |

### `trainer-movesets.json` shape (~1.9 MB)
Keyed by this build's species constant (same keys as `pokedex-index.json`),
each mapping to a list of the sets that appear across the three hacks:

```json
"ONIX": [
  { "source": "PlatinumKaizo", "hack": "Platinum Kaizo",
    "trainer": "Roughneck Robert", "gym": "Roark", "location": "Route 207",
    "level": 34, "item": "Choice Scarf", "ability": "Rock Head",
    "nature": "Impish", "gender": "",
    "moves": ["Explosion", "Earthquake", "Head Smash"] }
]
```

Fields present depend on source (`ability` only where the source lists it;
`gym` only for the xlsx hacks). Move names are kept verbatim from the source
(e.g. EK writes some in ALLCAPS for emphasis). A few Run & Bun entries have
an empty `moves` list because the source sheet left those cells blank.

### Counts
- **836** species, **5589** trainer sets
  (Run&Bun 1777, PlatinumKaizo 2040, EmeraldKaizo 1634, Rival 138).

### Regenerate (data lives in editable Google Docs, so refresh occasionally)

```bash
python3 docs/data/build_trainer_movesets.py
```

Zero third-party deps (stdlib xlsx reader). Fetches all three docs live and
rewrites `trainer-movesets.json`. Source URLs are at the top of the script.
Add `--local <dir>` to parse pre-downloaded copies
(`runbun.xlsx`, `plat.xlsx`, `ek_master.txt`, `ek_rival.txt`).
