# Gyms

One section per gym: leader, type, badge, level cap, team, and puzzle. Tracks our
hard-but-fair rebalance against vanilla.

> STATUS: stub. Generate baseline teams from trainer data after first build.
> Cross-link each leader's history to docs/writing/lore-ledger.md.

## Gym 1 — Pewter (Brock, Rock) — Boulder Badge
- Level cap: 14.
- Vanilla team: Geodude Lv12, Onix Lv14.
- Structure: a TRAINER POOL of 9 members that fields 6 (Party Size 6, Pool Rules
  Basic, Pool Prune Bst Match). Onix is tagged the ace (always fielded). At
  battle start the pool is BST-matched to the player: the game sums the player's
  team base-stat totals and fields the ace plus the five other members whose
  combined BST is closest to that total (implemented as the POOL_PRUNE_BST_MATCH
  prune in src/trainer_pools.c).
- Pool members (all Lv14, perfect IVs, no EVs, all female except genderless
  Stakataka; each runs a +Speed nature that lowers its unused attacking stat -
  Timid for the special attacker Glimmet, Jolly for the physical members, except
  the ultra-slow Stakataka which runs Adamant (+Atk/-SpA) instead of wasting a
  Speed boost):
  - ALOLAN GEODUDE (F) nicknamed "goku turd", Galvanize (Headbutt / Rock Tomb /
    Bulldoze / Mud-Slap)
  - ARON (F), Sturdy (Aerial Ace / Rock Tomb / Iron Head / Body Press)
  - GLIMMET (F), Corrosion (Acid Spray / Ancient Power / Mud Shot / Spikes)
  - AERODACTYL (F) nicknamed "Supa Burd", Pressure (Rock Blast / Wing Attack /
    Thunder Fang / Bulldoze)
  - STAKATAKA (genderless), Beast Boost (Rock Tomb / Heavy Slam / Bulldoze / Body
    Press) - Ultra Beast, BST 570, big power spike for a first gym
  - ROCKRUFF (F) nicknamed "sexy dawg", Vital Spirit (Rock Tomb / Sucker Punch /
    Attract / Play Rough)
  - HISUIAN GROWLITHE (F), Intimidate (Rock Tomb / Flame Wheel / Wild Charge /
    Morning Sun) - Fire/Rock; Wild Charge answers its 4x Water weakness, Morning
    Sun is recovery
  - CHEWTLE (F) nicknamed "sexy turt", Strong Jaw (Bite / Chilling Water / Ice
    Fang / Attract) - pure Water, the one non-Rock member. Strong Jaw boosts Bite
    and Ice Fang; Chilling Water is a utility Water move that lowers the target's
    Attack (weak damage off Chewtle's low SpA). (Rock Tomb was requested but
    Chewtle cannot learn it.)
  - ONIX (F) nicknamed "LongTurd", ACE, Sturdy (Swagger / Dig / Rock Tomb /
    Self-Destruct) - suicide-wall
- All movesets are level-cap-legal (verified with the moveset-legality skill).
- BST matching: POOL_PRUNE_BST_MATCH (src/trainer_pools.c) computes the player's
  team BST and keeps the ace plus the closest-total subset; ties break toward the
  higher total. Covered by a test in test/battle/trainer_control.c.
- History fragments: see BROCK-* in lore-ledger.md

## Gym 2 — Cerulean (Misty, Water) — Cascade Badge
- Level cap: 23 (`FLAG_BADGE02_GET` row in src/caps.c; see progression.md).
- Vanilla team: Staryu Lv18, Starmie Lv21.
- Structure: a TRAINER POOL of 10 water-types that fields 6 (Party Size 6, Pool
  Rules Basic, Pool Prune Bst Match). Two members are always fielded:
  - PSYDUCK is the FORCED LEAD (`POOL_TAG_LEAD`, always slot 1). Story-mandated:
    Psyduck is Misty's ever-present comic opener, so it always leads regardless
    of the player's team. See MISTY-* lore.
  - STARMIE is the ACE (`POOL_TAG_ACE`, always fielded last), the canon finisher.
  The remaining 4 slots are BST-matched to the player: the game sums the
  player's team base-stat totals and fields the four other members whose
  combined BST (added to Psyduck + Starmie) is closest to that total.
- BST matching: POOL_PRUNE_BST_MATCH (src/trainer_pools.c) now force-keeps BOTH
  ace- and lead-tagged members, then closest-total-matches the rest. This
  forced-lead behaviour is Misty-only (no other pool uses a LEAD tag). Covered by
  a test in test/battle/trainer_control.c ("...always fields the lead-tagged mon
  first...").
- Pool members (10, all Lv23 = at the cap, perfect IVs, no EVs, all female except genderless
  Starmie; each runs a +Speed nature that lowers its unused attacking stat).
  BST spread 295 (Horsea) - 525 (Vaporeon). Heavy RAIN theme: four Rain Dance
  setters (Psyduck, Horsea, Ludicolo, Vaporeon) feed Swift Swim (Horsea,
  Ludicolo, Goldeen) and Hydration (Vaporeon). All movesets cap-23 legal
  (verified with the moveset-legality skill):
  - PSYDUCK (F) LEAD, Swift Swim, Timid (Rain Dance / Scald / Psychic / Aerial
    Ace) - the story-mandated comic opener, sets rain turn 1.
  - HORSEA (F), Swift Swim, Timid (Rain Dance / Octazooka / Dragon Breath / Ice Beam)
  - BRIONNE (F), Liquid Voice, Timid (Echoed Voice / Rain Dance) - Liquid Voice
    makes Echoed Voice a ramping Water STAB.
  - PYUKUMUKU (F), Innards Out, Timid (Block / Spite / Double Team) - trap-staller;
    Block stops switching, Innards Out dumps its HP into the trapped foe on death.
  - CORSOLA (F), Regenerator, Timid (Scald / Ancient Power / Light Screen / Sucker Punch)
  - LUDICOLO (F), Swift Swim, Timid (Rain Dance / Giga Drain / Ice Beam / Scald)
    - self-sets rain and sweeps at doubled Speed.
  - AZUMARILL (F), Sap Sipper, Jolly (Perish Song / Whirlpool / Bulldoze /
    Waterfall) - Whirlpool + Perish Song trap; Sap Sipper walls Grass.
  - GOLDEEN (F), Swift Swim, Naive (Scald / Drill Run / Poison Jab / Icy Wind)
  - VAPOREON (F), Hydration, Timid (Rain Dance / Water Pulse / Ice Beam / Wish)
    - the wall; Rain Dance + Hydration = status-proof, Wish heals the pool.
  - STARMIE (genderless) ACE, Natural Cure, Timid (Water Pulse / Psybeam /
    Thunderbolt / Ice Beam) - fast BoltBeam finisher, always fielded.
- Gimmick: no BUG-type POKéMON allowed in the gym (party check on entry; the Gym
  Guy shoves you out). See MISTY-07.
- History fragments: see MISTY-* in lore-ledger.md.

## Gym 3 — Vermilion (Lt. Surge, Electric) — Thunder Badge
- Vanilla team: Voltorb Lv21, Pikachu Lv18, Raichu Lv24.
- Rebalanced team: (TBD)
- Gate: vanilla FRLG already gates the gym behind Cut (the cuttable tree at
  (19,24) is the only entrance to the gym pocket; Cut comes from the S.S. Anne
  Captain). Reframed as Surge's "first trial": cross the S.S. Anne, reach the
  Captain, earn Cut. Framing lives in the Captain's reveal + ambient lines; no
  extra gate object. See SURGE-06.
- Puzzle: trash-can "discipline/endurance" trial (SURGE-GIMMICK).
- History fragments: see SURGE-* in lore-ledger.md (payoff = S.S. Anne Captain).

## Gym 4 — Celadon (Erika, Grass) — Rainbow Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD)
- Gimmick: canon "ladies only" flower gym, reframed - the gym women are Brock's
  "previous sponsors" (his exes) taking refuge; Erika hosts them all and is not one
  herself. Coy, cross-links the Brock arc. See ERIKA-EXES.
- Related town gimmick: the Route 16 bikers fled Celadon in fear of the
  "perfume/medicine master" and camp on the Cycling Road with their POISON types
  (ERIKA-BIKERS).
- History fragments: see ERIKA-* in lore-ledger.md. Mystique by design - the town
  trades many contradictory legends (poison/medicine dominant) and none is
  confirmed; NO plain telling.

## Gym 5 — Fuchsia (Koga, Poison) — Soul Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD)
- Gimmick: canon invisible-wall maze, reframed - it's a deliberate PROTESTER-
  REPELLENT (petitioners who come to shout at Koga about the smog get lost and give
  up). See KOGA-REVEAL.
- History fragments: see KOGA-* in lore-ledger.md. Hidden layer: Koga is the CEO of
  KOGA INDUSTRIES (Kanto's power utility); the whole Fuchsia area argues over him as
  a necessary evil, and the gym insiders reveal he's a spin doctor. Semi-plain arc.

## Gym 6 — Saffron (Sabrina, Psychic) — Marsh Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD)
- Gimmick: canon teleport-panel maze, reframed as a POSSESSION trial - every trainer
  is forced to fight and gives a contradictory false direction to reach Sabrina; the
  Gym Guide (also possessed) warns "trust no one, not even me." See SABRINA-GYM.
- Arc: she went cold to cage her power and folds the town's minds into her own; losing
  to you makes her LAUGH, breaking the spell and freeing everyone unharmed. Payoff =
  Mr. Psychic. See SABRINA-* in lore-ledger.md.

## Gym 7 — Cinnabar (Blaine, Fire) — Volcano Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD)
- Gimmick: canon quiz-door trivia gate, reframed as Blaine testing the MIND before
  the POKéMON (raw power without wisdom is what made a monster). Mechanic unchanged.
- Arc: Blaine helped create MEWTWO at the POKéMON MANSION on Dr. Fuji's team; it broke
  loose and burned everything, and his fire persona / quizzes are his guilt and
  penance. Payoff = a Lab scientist + the Fuji photo + the signed Mansion diary
  fragments. Canon-blend, tag canon-check. See BLAINE-* in lore-ledger.md.

## Gym 8 - Viridian (Giovanni, Ground) - Earth Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD; Earth cap is 63)
- Gimmick: the gym is LOCKED the entire game (canon; opens only after badges 2-7)
  and its LEADER is never seen. We reframe the locked door as the town's civic
  blind spot: Viridian is earnestly, proudly devoted to a LEADER nobody has ever
  met ("away… on business"), while that leader is the ROCKET boss you have been
  chasing. No mechanical change; the framing lives in dialogue.
- Arc (UNIQUE — recurring antagonist, three battles): Giovanni is hiding in plain
  sight as the absent Viridian LEADER. The region carries two absences (unseen
  ROCKET boss / never-there LEADER) and the player rhymes them until the gym opens
  and canon reveals they are one man. Engine = the SELF-MADE MAN FROM THE DIRT (no
  son thread): strength is worth, being weak once was terror, so he built ROCKET
  from nothing; when he loses he gives up the empire and walks off to chase
  strength alone. GROUND-type is the through-line (EARTHQUAKE TM, "from the ground
  up"). The three fights (Rocket Hideout -> Silph Co -> Viridian Gym) are
  reflavored to escalate the weight but stay hard-but-fair; payoff is semi-plain,
  landed by canon's own gym reveal + the Fame Checker.
- History fragments: see GIOVANNI-* in lore-ledger.md.
