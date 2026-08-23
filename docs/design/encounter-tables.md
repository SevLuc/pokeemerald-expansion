# Encounter Tables — Design & Balancing Methodology

Status: DESIGN (agreed decisions; generator + final data pending).
Scope: wild encounter redistribution for the whole region (FireRed primary,
LeafGreen mirrored identical).

## Goal

Redistribute all wild encounters so the run feels fresh, is fair-but-hard, and
every kept Pokemon is obtainable before the Elite Four. Encounter tables are
built by a reproducible generator, then verified.

## Core decisions

1. **Base forms only (family roots).** Each placed encounter is the evolution
   family's ROOT (lowest pre-evo), computed over the full evolution graph. Catch
   the base, evolve up. Rule: *if any member of an evo line is catchable, the
   whole line is* — so we only place the root. Roots have no evolution-level
   floor, so any level band is legal for them. NEVER place an evolved form
   (would imply catching below its evo level). Finals with no pre-evo (Absol,
   Tauros, Skarmory, etc.) are themselves roots and placed directly.

2. **Coverage contract: everything before the E4.** Every family root in the
   kept pool (see `docs/overview/encounters-candidates.md`) must appear in at
   least one FireRed table on a map reachable before the Elite Four. Kanto
   mainland is the coverage backbone; Sevii 1-3 is pre-E4 too; Sevii 4-7,
   Cerulean Cave, Unknown Dungeon are post-game (bonus/duplicates only).

3. **Method splits are independent tables.** Grass (land), Surf (water),
   fishing, and rock-smash are separate encounter pools per map.
   - **Water is unified:** Old Rod, Good Rod, Super Rod, AND Surf draw from the
     SAME per-map water pool (no method-gated exclusives). Implementation:
     fishing rod `groups` all point at the full slot range; Surf `water_mons`
     mirrors the same species pool.

4. **Equal chance.** Every slot in a table is equally likely — no vanilla
   rarity ladder. Implemented by flattening the shared `encounter_rates` arrays
   in `src/data/wild_encounters.json` (land 12 equal, water 5 equal, fishing
   rod-groups equalized). One global edit; no engine change. Rarity no longer
   gates power — **area/progression gates power instead.**

5. **Two axes — separate concerns:**
   - **Difficulty axis = EFFECTIVE BST at the split (see below).** A caught base
     is evolved immediately as far as the player can, so the real battle metric
     is the best form reachable at that point — not the base's current BST.
   - **Flavor/coverage axis = biome & progression.** Which line goes roughly
     where is secondary. Pseudo-legend lines stay ~300 effective for a long time
     (evolve at Lv30+), so they can sit mid-game without breaking a fight — a
     Dratini is weak until well after you catch it. Lines that spike effective
     BST early (fast/friendship evolvers) are the ones that get gated later.

### Effective BST (the difficulty metric)

For a given split, a species' effective BST = the highest form it can reach,
walking its evo chain with these reachability rules:

- **Level-up evo:** reachable if `evo_level <= split level cap`.
- **Friendship (and other level-0 immediate) evo:** always reachable (caught
  mons start at max friendship). Encoded as `EVO_LEVEL, 0, target,
  CONDITIONS(...)`.
- **Stone / trade / held-item / scroll evo (`EVO_ITEM`, `EVO_TRADE`, `EVO_SPIN`,
  scroll/script triggers):** locked until the **Erika split** (Celadon Dept
  Store sells all evo + trade items). Before Erika, use the pre-item-evo form.

Examples at the Brock split (cap 14, no items): Caterpie → Butterfree (395);
Azurill → Marill (250, friendship) but NOT Azumarill (Lv18 > cap); Dratini stays
300 (Dragonair Lv30); Geodude stays 300 (Golem needs trade item, Erika+);
Eevee → Espeon/Umbreon (525, friendship). This lifts the low bases and collapses
variance, exactly the point of the metric.

Refinement for the generator: read `CONDITIONS` to tell friendship (immediate)
from beauty/other level-0 conditions (e.g. Feebas → Milotic) that are not truly
immediate; the quick parser currently treats all level-0 as immediate.

6. **Light biome.** Areas keep a light thematic identity (forest = Bug/Grass,
   cave = Rock/Ground, etc.). Biome is a tiebreak within a tier, not a hard
   filter — EXCEPT where explicitly pinned (see Viridian Forest below).

7. **Vanilla level bands kept** per area (each species' min/max levels stay
   within the area's existing FRLG envelope).

## Balancing rule (the important part)

**Balance is enforced at the GROUP level, not per route.** A "group" = all areas
reachable before a given gym. Individual routes do NOT need to increase linearly
in BST across the region. What matters is the aggregate:

- the **player's expected team-average BST distribution** for that group, where
  the player catches ~1 mon per area (nuzlocke-style, uniform among the area's
  equal-chance slots).

This is why encounters are done in splits: a low-BST biome route is balanced by
a higher-BST route in the same group, so the group average and variance land on
target while each route keeps its own flavor.

### Per-gym target distribution

For each gym, tune the pre-gym group so the player team-average BST forms a
clean bell with ~5% tails (only ~5% of runs roll the strong extreme, ~5% the
weak extreme, most cluster at the mean). Uniform per-area selection makes the
team-average approximately normal automatically (central limit); tight per-area
current-BST windows control the variance.

Knobs:
- **Group center** = where the player sits vs the gym (window position).
- **Group spread** = tail width (window width; narrower = more consistent runs).

The generator computes the player team-avg mean / std / 90% band the SAME way
the gym's own team distribution is computed, and calibrates the group to it.

## Gym reference: Brock (NOT changed)

Brock is fixed. His pool is 9, fields 6 (uniform selection ⇒ ~5% extreme tails
already). Current-BST reference:

- Brock team-average across all C(9,6)=84 teams: **mean 374, std 24, 90% band
  325-409**. Weakest-6 avg 316; the two Ultra Beasts (Aerodactyl 515, Stakataka
  570) drive most of the spread.

### Pre-Brock group (Route 1, Route 2, Route 22, Viridian Forest)

- **Viridian Forest is pinned to Bug/Grass** biome (lower BST by nature). The
  other three pre-Brock routes carry higher BST to compensate, holding the group
  average on target.
- Balanced on EFFECTIVE BST at cap 14 / no items. Viridian Forest sits ~294
  effective (bugs mostly evolve past Lv14, so weak at Brock); Routes 1/2/22 run
  ~370 to hold the group average.
- Recommended group target **355** → player team-avg **mean 351, std 12, 90%
  band 332-370** (vs Brock fixed mean 374, std 24, band 325-409). Fair-hard:
  ~5% high-roll to ~370 (Brock's median), ~5% low-roll to ~332, most ~351.
  Group target is the per-gym difficulty knob.

## Generator (to build)

Reproducible script: reads the kept pool + `species_info` (BST, types,
evolutions), resolves family roots, places roots by current-BST group windows +
light biome, unifies water methods, flattens rates for equal chance, emits the
`sX_FireRed` / mirrored `sX_LeafGreen` entries into
`src/data/wild_encounters.json`. Then asserts:
- 100% pre-E4 coverage of every root;
- no evolved form placed;
- per-gym player team-avg within tolerance of its target (mean & spread);
and prints a coverage + per-gym fairness report.

### Data-parsing notes (for the generator)

BST from `species_info` must resolve `#define` stat macros and config ternaries
(`P_UPDATED_STATS >= GEN_x ? new : old` → take the updated value). Evolution
target = the 3rd field of each `{METHOD, PARAM, TARGET, ...}` tuple; strip
`CONDITIONS(...)` first (it holds trade-PARTNER species, not targets). Family
root via the full evo graph. Pending cleanups: ~3 macro-typed species
(Rotom/Cottonee/Igglybuff type2) and a few form-suffixed bases
(Shellos/Sinistea/Gimmighoul/Basculin/Morpeko/Mimikyu).

## Open items

- Group centers for every gym (difficulty curve) — set one center per gym.
- Keep or drop ultra-low tiddlers (Caterpie/Azurill/etc.) in early groups.
- Story order per group (which areas belong to which pre-gym group).
