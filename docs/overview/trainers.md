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

Note: Omega runs RANDOM AI on the two early Giovanni fights (Rounds 1 and 2), the
same idea chosen for the Twitch rival. Precedent for keeping those AI-light.

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
| Lorelei | `TRAINER_ELITE_FOUR_LORELEI` | `TRAINER_ELITE_FOUR_LORELEI_2` | Pool drafted (see elite-four.md); fielded subset + wiring TODO |
| Bruno | `TRAINER_ELITE_FOUR_BRUNO` | `TRAINER_ELITE_FOUR_BRUNO_2` | TODO |
| Agatha | `TRAINER_ELITE_FOUR_AGATHA` | `TRAINER_ELITE_FOUR_AGATHA_2` | TODO |
| Lance | `TRAINER_ELITE_FOUR_LANCE` | `TRAINER_ELITE_FOUR_LANCE_2` | TODO |
| Champion (rival) | `TRAINER_CHAMPION_FIRST_*` | `TRAINER_CHAMPION_REMATCH_*` | TODO (Buhrito) / DONE (Twitch draft) |

## By map
(Pallet → Viridian → Route 1 → ... — fill in from data)
