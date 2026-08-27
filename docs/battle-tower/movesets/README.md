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

## Source
Sets are transcribed from **Smogon** competitive data via `data.pkmn.cc`
(machine-readable). For each Pokemon, sets are gathered from the newest
generation where it has data, falling back through older gens, deduplicated
by move signature, and capped at ~8 distinct sets. Singles formats only
(doubles/VGC excluded). Tera types dropped (gimmick off). Z-crystal and
Mega-Stone sets are excluded from non-Mega entries.

**Every move / item / ability / nature constant is validated against this
build's own headers** (0 unresolved at generation time). EVs use the 6-key
HP/Atk/Def/SpAtk/SpDef/Speed format.

Emerald Kaizo and Run & Bun sets will be appended as additional sets per
Pokemon (with `source` tagged accordingly) once those documents are provided.

## Coverage
- **720 of 769 entries** have movesets — **4,538 sets total**, every
  constant validated against this build (0 invalid).
- **Smogon-sourced:** the standard roster, regional/alt formes, restricted
  tier, Eviolite NFE, and the **48 official Gen 6 Megas** (extracted from
  Smogon's base-species-plus-Mega-Stone sets).
- **Constructed (37):** low-usage Gen 8/9 mons and NFE Eviolite picks with no
  competitive data anywhere (Doublade, Type: Null, Vullaby, Duosion, Rufflet,
  Kirlia, Sneasel-Hisui, Dachsbun, Klawf, Spidops, …). Built from in-build
  stats/movepool and tagged `source: "Constructed (…)"`. Toxtricity Low-Key
  shares the Amped forme's sets.

## Still pending
- **49 custom Megas** — the Pokemon Legends: Z-A Megas (2025-2026), not in
  Smogon yet. `megas.json` lists them with empty `sets` and a `_note`; they
  await your source doc (same flow as Kaizo / Run & Bun).

See `_report.json` for the exact `official_mega`, `constructed`, and
`awaiting_za_docs` lists.
