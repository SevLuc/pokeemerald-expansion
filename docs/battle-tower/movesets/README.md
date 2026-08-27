# Battle Tower Movesets

Per-Pokemon competitive movesets for the rental Battle Tower mode. See
`../roster.md` for the full roster and locked design decisions.

## Files
| File | Contents |
|---|---|
| `gen1.json` … `gen9.json` | Standard fully-evolved mons, grouped by introduction generation |
| `regional.json` | Alolan / Galarian / Hisuian / Paldean finals |
| `altformes.json` | Alternate battle formes (Rotom, Wormadam, Oricorio, Lycanroc, …) |
| `restricted.json` | Restricted tier (legendaries / mythicals / paradox / ultra beasts) |
| `eviolite.json` | Eviolite NFE picks |
| `megas.json` | Mega Evolutions (rental-mode only) — see status below |
| `_report.json` | Coverage report + `needs_construct` list + any constant warnings |

## Per-set schema
```json
{
  "species": "SPECIES_GARCHOMP",
  "displayName": "Garchomp",
  "tier": "standard",
  "sets": [
    {
      "name": "Swords Dance",            // set label
      "role": "setup sweeper",           // inferred play style
      "tier": "ou",                      // Smogon format the set came from
      "item": "ITEM_LOADED_DICE",
      "ability": "ABILITY_ROUGH_SKIN",
      "nature": "NATURE_JOLLY",
      "evs": {"hp":0,"atk":252,"def":0,"spatk":0,"spdef":4,"speed":252},
      "moves": ["MOVE_SWORDS_DANCE","MOVE_SCALE_SHOT","MOVE_EARTHQUAKE","MOVE_FIRE_FANG"],
      "source": "Smogon data.pkmn.cc (gen9 ou)",
      "notes": "Fire Fang/Dragon Tail"   // slashed alternatives + Hidden Power type
    }
  ]
}
```

## Sources
Each set carries a `source`. Three feeds are merged per Pokemon, deduplicated
by move signature, up to 14 sets per Pokemon (Smogon first, then Run & Bun and
Emerald Kaizo interleaved so both hacks are represented):

- **Smogon** (`data.pkmn.cc`, machine-readable): newest gen where the Pokemon
  has data, falling back through older gens. Singles formats only (doubles/VGC
  excluded). Tera dropped. Z-crystal / Mega-Stone sets excluded from non-Mega
  entries. Official Gen 6 Megas extracted from base-species + Mega-Stone sets.
- **Run & Bun** (`Trainer Battles` doc): every trainer's Pokemon with an
  explicit moveset, grouped by species and deduped. Includes late-game / E4 /
  champion full sets with items.
- **Emerald Kaizo** (`EK Mastersheet`): same extraction from the EK trainer
  data.

**Every move / item / ability / nature constant is validated against this
build's own headers** (0 unresolved). EVs use the 6-key
HP/Atk/Def/SpAtk/SpDef/Speed format.

### Caveats on the hack sets
- The Run & Bun / Emerald Kaizo docs list moves, item, nature and (R&B only)
  ability, but **not EVs** — so `evs` on those sets is a role-based default and
  `notes` says so. Adjust before use if exact spreads matter.
- Both hacks rebalance some moves/abilities. Sets are transcribed **as-is**;
  constants all resolve in this build, but a move's *power/effect* may differ
  from the hack. Treat these as playstyle templates, not exact clones.
- Hack sets that hold a Mega Stone are attached to the **base species** (as the
  doc lists them), not the separate `_MEGA` entry.

## Coverage
- **All 769 entries** have movesets — **6,172 sets total**, every constant
  validated against this build (0 invalid).
- By source: **Smogon 4,491 · Run & Bun 1,076 · Emerald Kaizo 506 ·
  Constructed (niche) 47 · Constructed Z-A Mega 52**.
- Niche constructed sets cover low-usage Gen 8/9 mons and NFE Eviolite picks
  with no competitive data anywhere (Doublade, Type: Null, Vullaby, Duosion,
  Rufflet, Kirlia, Sneasel-Hisui, Dachsbun, Klawf, Spidops, …). Toxtricity
  Low-Key shares the Amped forme's sets.
- The **49 custom Z-A Megas** are built from this build's own type/ability/stats
  (the Legends Z-A typings/abilities are already in the species data), with
  playstyles informed by published Z-A build guides. Abilities are taken
  verbatim from the build (e.g. Feraligatr = Dragonize, Excadrill = Piercing
  Drill). Physical vs special EV spreads inferred from move categories.
- Gen 9 / regional / alt-forme entries get no hack sets (those species do not
  exist in the Emerald-based hacks) — Smogon-only there.

See `_report.json` for the exact `official_mega`, `constructed`, and
`za_constructed` lists.
