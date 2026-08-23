# Trainers

Master list of trainer teams, in map order, for balance review.

> STATUS: stub. Generate baseline from src/data/trainers.party
> (+ trainers_frlg.h if present) after first build.
> Update in the same PR as any team change (per CLAUDE.md).

## Important trainers (worklist, Omega-weight)

Mirrors the important-trainer set from FireRed Omega (Questionable Specimen's doc):
every rival fight, every gym leader, all three Giovanni fights, the Elite Four, and
the Champion (plus the post-game E4 + Champion rematch). Each of these gets a
deliberate, custom team. Omega's counts line up 1:1 with FRLG ("Rival A" = the
Route 22 early fight); nothing extra to create.

Status: **DONE** = custom team drafted in `src/data/trainers_frlg.party`. **TODO** =
still the vanilla FRLG baseline, needs a hand-built team.

AI: as of 2026-08-23 every non-Twitch trainer runs at least `Check Bad Move /
Try To Faint`. Gym leaders, Elite Four, Champion (+ rematches) and the Buhrito
rival run the full `Check Bad Move / Try To Faint / Check Viability`. The two
early Giovanni (Omega) boss fights are NO LONGER AI-light; they now faint like
everyone else. Only the Twitch rival (`TRAINER_RIVAL_TWITCH_*`) keeps RANDOM AI,
as a Twitch Plays Pokemon homage.

### Rivals
Each rival fight = the Buhrito path (vanilla 3 starter-variants, counters the player)
and the Twitch path (single team, always Abby). Buhrito currently reuses the vanilla
"TERRY" teams; Twitch has its own TPP-roster constants.

| Omega | Fight | Buhrito constants | Buhrito | Twitch constant | Twitch |
|---|---|---|---|---|---|
| Rival 1 | Oak's Lab | `TRAINER_RIVAL_OAKS_LAB_{SQUIRTLE,BULBASAUR,CHARMANDER}` | TODO | `TRAINER_RIVAL_TWITCH_OAKS_LAB` | DONE |
| Rival A | Route 22 early | `..._ROUTE22_EARLY_*` | TODO | `..._TWITCH_ROUTE22_EARLY` | DONE |
| Rival 2 | Cerulean | `..._CERULEAN_*` | TODO | `..._TWITCH_CERULEAN` | DONE |
| Rival 3 | S.S. Anne | `..._SS_ANNE_*` | TODO | `..._TWITCH_SS_ANNE` | DONE |
| Rival 4 | Pokemon Tower | `..._POKEMON_TOWER_*` | TODO | `..._TWITCH_POKEMON_TOWER` | DONE |
| Rival 5 | Silph Co | `..._SILPH_*` | TODO | `..._TWITCH_SILPH` | DONE |
| Rival 6 | Route 22 late | `..._ROUTE22_LATE_*` | TODO | `..._TWITCH_ROUTE22_LATE` | DONE |
| Champion | Indigo Plateau | `TRAINER_CHAMPION_FIRST_*` (+ rematch `TRAINER_CHAMPION_REMATCH_*`) | TODO | `..._TWITCH_CHAMPION` | DONE |

Twitch teams are DRAFT: authentic TPP species + nicknames, levels pegged to the caps,
moves auto-filled (level-up), IVs placeholder. Refine movesets/IVs on the balance pass.

#### Rival (Locke) - generated nuzlocke teams
The default (non-Twitch) rival, Locke, plays nuzlocke-style: his party is BUILT AT
BATTLE TIME instead of coming from a static `trainers.party` entry. A per-save random
seed (stored in two event vars, rolled once at new game) drives the generation, so
every playthrough gives Locke a different but internally consistent team, and the same
save always reproduces the same team. Implementation lives in `src/rival_nuzlocke.c`,
`include/rival_nuzlocke.h`, and the per-fight data in `src/data/rival_nuzlocke_battles.h`;
it hooks into `CreateNPCTrainerParty` in `src/battle_main.c`. The Twitch rival is a
separate character and is completely unaffected.

Scope:
- Applies to ALL Locke fights EXCEPT Oak's Lab. The Oak's Lab fight keeps its static,
  starter-only team (the tutorial loss).
- The Route 22 early fight fields 4 mons. Every fight from Cerulean onward fields 6.
- Levels match the vanilla rival's per-fight ACE level: 12 / 18 / 20 / 25 / 40 / 53 /
  63, and 75 for the Champion rematch.

How a team is built:
- Starter (his ace): the type that COUNTERS the player's starter, kept the whole game.
  Which of the three trainer-id variants is used encodes the starter, so it is fixed
  per save. The starter is ALWAYS on the team but NEVER leads.
- Lead (slot 0): the LEAST-WEAK mon (fewest type weaknesses) leads. The starter is
  benched from the lead slot even when it would otherwise qualify.
- Non-starter mons: one is rolled per "visited area" from that area's own wild
  encounter table (land / water / fishing), walked in a fixed story order. Dupes
  clause: no repeated species. Each rolled mon is evolved to whatever stage its level
  allows.
- When a fight's visited-area pool has more candidates than team slots, members are
  chosen for TYPE COVERAGE: prefer mons that resist the starter's weaknesses and that
  minimize shared team weaknesses.

Visited-area pools per fight (cumulative, from `rival_nuzlocke_battles.h`, 34 areas total):

| Fight | Areas added at this fight |
|---|---|
| Route 22 early | Route 1, Viridian City (fishing), Route 22 |
| Cerulean | Routes 2-4, Viridian Forest, Mt Moon, Cerulean (fishing), Routes 24-25 |
| S.S. Anne | Routes 5-6, Vermilion (fishing), Route 11 |
| Pokemon Tower | Routes 8-10, Rock Tunnel |
| Silph Co | Route 7, Celadon (fishing), Routes 12-18 |
| Route 22 late | Routes 19-21 (water), Seafoam |
| Champion | Victory Road, Route 23 |

(Later fights include all earlier areas, so the pool grows across the game.)

### Gym leaders
| Leader | Constant | Status |
|---|---|---|
| Brock | `TRAINER_LEADER_BROCK` | TODO |
| Misty | `TRAINER_LEADER_MISTY` | TODO |
| Lt. Surge | `TRAINER_LEADER_LT_SURGE` | Pool of 10 Electric, fields 6, ace Raichu, Lv27 (see gyms.md) |
| Erika | `TRAINER_LEADER_ERIKA` | TODO |
| Koga | `TRAINER_LEADER_KOGA` | TODO |
| Sabrina | `TRAINER_LEADER_SABRINA` | TODO |
| Blaine | `TRAINER_LEADER_BLAINE` | TODO |
| Giovanni (Viridian gym) | `TRAINER_LEADER_GIOVANNI` | TODO |

### Giovanni (3 fights)
| Fight | Constant | Status |
|---|---|---|
| Round 1, Rocket Hideout (RANDOM AI) | `TRAINER_BOSS_GIOVANNI` | TODO |
| Round 2, Silph Co (RANDOM AI) | `TRAINER_BOSS_GIOVANNI_2` | TODO |
| Viridian gym | `TRAINER_LEADER_GIOVANNI` | TODO |

### Elite Four + Champion
| Slot | First | Rematch | Status |
|---|---|---|---|
| Lorelei | `TRAINER_ELITE_FOUR_LORELEI` | `TRAINER_ELITE_FOUR_LORELEI_2` | TODO |
| Bruno | `TRAINER_ELITE_FOUR_BRUNO` | `TRAINER_ELITE_FOUR_BRUNO_2` | TODO |
| Agatha | `TRAINER_ELITE_FOUR_AGATHA` | `TRAINER_ELITE_FOUR_AGATHA_2` | TODO |
| Lance | `TRAINER_ELITE_FOUR_LANCE` | `TRAINER_ELITE_FOUR_LANCE_2` | TODO |
| Champion (rival) | `TRAINER_CHAMPION_FIRST_*` | `TRAINER_CHAMPION_REMATCH_*` | TODO (Buhrito) / DONE (Twitch draft) |

## By map
(Pallet → Viridian → Route 1 → ... — fill in from data)
