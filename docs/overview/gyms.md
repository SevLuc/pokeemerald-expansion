# Gyms

One section per gym: leader, type, badge, level cap, team, and puzzle. Tracks our
hard-but-fair rebalance against vanilla.

Level tiering (all gyms + Elite Four): only the ACE sits at the level cap. Other
members sit below it - cap-2 for the bulk. The OPENER (slot 0, the first mon sent)
is always cap-4, applied by code at party-build time for any Leader/Elite-Four
class trainer, so it holds even when the lead is an untagged random draw from the
pool (Brock, Lt. Surge). Trainers with a forced LEAD tag (Misty's Psyduck) get the
same cap-4 on that fixed mon. This overrides whatever level the opener's mon is
authored at in trainers_frlg.party. The party is rebuilt fresh at the start of
every battle. Code: CreateNPCTrainerPartyFromTrainer in src/battle_main.c.

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
- Pool members (non-ace all Lv12 = cap-2; ace Onix Lv14; no forced lead, so no
  cap-4 member. Perfect IVs, no EVs, all female except genderless
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
- Pool members (10; Starmie ace Lv23 = cap, Psyduck lead Lv19 = cap-4, the other
  8 Lv21 = cap-2. Perfect IVs, no EVs, all female except genderless
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
- Level cap: 27 (`FLAG_BADGE03_GET` row; see progression.md).
- Vanilla team: Voltorb Lv21, Pikachu Lv18, Raichu Lv24.
- Structure: a TRAINER POOL of 10 Electric-types that fields 6 (Party Size 6,
  Pool Rules Basic, Pool Prune Bst Match). Raichu is the ACE (always fielded
  last). The other 5 slots are BST-matched to the player: the game sums the
  player's team base-stat totals and fields the ace plus the five other members
  whose combined BST is closest to that total (POOL_PRUNE_BST_MATCH in
  src/trainer_pools.c). No forced lead (Surge-only difference from Misty).
- Pool members (10; Raichu ace Lv27 = cap, the other 9 Lv25 = cap-2; no forced
  lead, so no cap-4 member. Perfect IVs, no EVs; no nicknames).
  All natures are +Speed except the two slow bruisers Iron Hands (Brave) and
  Pincurchin (Quiet). The +Speed natures shed the UNUSED attacking stat: Timid
  for pure special attackers, Jolly for pure physical, Naive for the two mixed
  members (Raichu, H-Electrode) so neither attacking stat is cut. BST spread
  405 (Pachirisu) - 570 (Iron Hands). Momentum/VoltTurn theme: six members carry
  Volt Switch or a pivot, Pincurchin's Electric Surge and Iron Hands' own
  Electric Terrain power the pool's Electric moves and Quark Drive:
  - JOLTEON (M), Volt Absorb, Timid (Thunderbolt / Magnet Rise / Trailblaze / Yawn)
  - ROTOM-FROST (genderless), Levitate, Timid (Blizzard / Thunderbolt / Light
    Screen / Reflect) - Blizzard is trainer-set (form move, not in the learn
    pool in this build; trainer parties are not learnset-bound).
  - IRON HANDS (genderless), Quark Drive, Brave (Electric Terrain / Drain Punch /
    Thunder Punch / Ice Punch) - Ultra-ish power pick, BST 570; self-sets terrain
    to trigger its own Quark Drive.
  - HISUIAN ELECTRODE (genderless), Static, Naive (Chloroblast / Thunderbolt /
    Ice Ball / Self-Destruct) - Electric/Grass, fast suicide disruptor.
  - HELIOLISK (M), Dry Skin, Timid (Thunderbolt / Hyper Voice / Signal Beam /
    Grass Knot)
  - MORPEKO (F), Hunger Switch, Jolly (Wild Charge / Seed Bomb / Stomping Tantrum
    / Super Fang) - Aura Wheel is locked by the cap (L55), so Wild Charge is its
    Electric STAB.
  - TOGEDEMARU (M), Iron Barbs, Jolly (Nuzzle / Iron Head / Endeavor / Volt Switch)
  - PINCURCHIN (F), Electric Surge, Quiet (Rising Voltage / Self-Destruct /
    Muddy Water / Thunder Wave) - the slow terrain setter; Rising Voltage
    doubles under its own terrain.
  - PACHIRISU (M), Volt Absorb, Timid (Nuzzle / Light Screen / Mud Slap / Volt
    Switch) - pure annoyer; Super Fang is locked by the cap (L37).
  - RAICHU (F), ACE, Static, Naive (Extreme Speed / Thunderbolt / Surf / Grass
    Knot) - fast mixed cleaner. Extreme Speed is trainer-set (not in the FRLG
    Pichu/Pikachu/Raichu learn pool in this build; it was only ever an event
    move).
- Two off-learnset moves are set directly on the trainer mons (legal for trainer
  parties, which are not bound by learnset legality): Rotom-Frost's Blizzard and
  Raichu's Extreme Speed. Every other move is cap-27 legal (verified with the
  moveset-legality skill).
- Gate: vanilla FRLG already gates the gym behind Cut (the cuttable tree at
  (19,24) is the only entrance to the gym pocket; Cut comes from the S.S. Anne
  Captain). Reframed as Surge's "first trial": cross the S.S. Anne, reach the
  Captain, earn Cut. Framing lives in the Captain's reveal + ambient lines; no
  extra gate object. See SURGE-06.
- Puzzle: trash-can "discipline/endurance" trial (SURGE-GIMMICK).
- History fragments: see SURGE-* in lore-ledger.md (payoff = S.S. Anne Captain).

## Gym 4 — Celadon (Erika, Grass) — Rainbow Badge
- Vanilla team: Victreebel Lv29, Tangela Lv24, Vileplume Lv29 (fixed 3).
- Rebalanced team: a TRAINER POOL of 10 Grass-types that fields 6 (Party Size 6,
  Pool Rules Basic, Pool Prune Bst Match). Vileplume is the ACE (always fielded
  last). No forced lead (Surge-style), so no cap-4 member. The other 5 slots are
  BST-matched to the player (POOL_PRUNE_BST_MATCH in src/trainer_pools.c). Perfect
  IVs, no EVs, no nicknames; all mons female (flower-gym flavor). Sun is the pool's
  backbone: six members carry Sunny Day and four more have Chlorophyll to abuse it.
- Levels: cap 35 (`FLAG_BADGE04_GET` row in src/caps.c). Vileplume ace Lv35 = cap;
  the other 9 pool members Lv33 = cap-2. Pool (ability / nature / moves):
  - VILEPLUME (ace), Effect Spore, Timid (Sleep Powder / Giga Drain / Sludge Bomb / Strength Sap)
  - TANGROWTH, Chlorophyll, Hasty (Sunny Day / Solar Beam / Ancient Power / Earthquake)
  - MEOWSCARADA, Overgrow, Jolly (Flower Trick / Throat Chop / Acrobatics / Low Kick)
  - EXEGGUTOR, Chlorophyll, Timid (Sunny Day / Solar Beam / Psychic / Sludge Bomb)
  - ROSERADE, Technician, Timid (Giga Drain / Sludge Bomb / Dazzling Gleam / Mud Shot)
  - VICTREEBEL, Chlorophyll, Timid (Sunny Day / Solar Beam / Sludge Bomb / Weather Ball)
  - JUMPLUFF, Chlorophyll, Jolly (Sunny Day / Leech Seed / Substitute / Acrobatics)
  - MEGANIUM, Leaf Guard, Jolly (Leaf Blade / Earthquake / Sunny Day / Synthesis)
  - PARASECT, Dry Skin, Adamant (Spore / Fell Stinger / Seed Bomb / Substitute) - deliberate meme pick
  - VENUSAUR, Chlorophyll, Timid (Sunny Day / Solar Beam / Sludge Bomb / Earth Power)
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
- Rebalanced team: (TBD — still the vanilla-count roster, fixed team).
- Levels (tiered, cap 43): Koffing Lv39 (lead, cap-4), Muk Lv41 (cap-2), Koffing
  Lv41 (cap-2), Weezing Lv43 (ace, cap).
- Gimmick: canon invisible-wall maze, reframed - it's a deliberate PROTESTER-
  REPELLENT (petitioners who come to shout at Koga about the smog get lost and give
  up). See KOGA-REVEAL.
- History fragments: see KOGA-* in lore-ledger.md. Hidden layer: Koga is the CEO of
  KOGA INDUSTRIES (Kanto's power utility); the whole Fuchsia area argues over him as
  a necessary evil, and the gym insiders reveal he's a spin doctor. Semi-plain arc.

## Gym 6 — Saffron (Sabrina, Psychic) — Marsh Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD — still the vanilla-count roster, fixed team).
- Levels (tiered, cap 43): Kadabra Lv39 (lead, cap-4), Mr. Mime Lv41 (cap-2),
  Venomoth Lv41 (cap-2), Alakazam Lv43 (ace, cap).
- Gimmick: canon teleport-panel maze, reframed as a POSSESSION trial - every trainer
  is forced to fight and gives a contradictory false direction to reach Sabrina; the
  Gym Guide (also possessed) warns "trust no one, not even me." See SABRINA-GYM.
- Arc: she went cold to cage her power and folds the town's minds into her own; losing
  to you makes her LAUGH, breaking the spell and freeing everyone unharmed. Payoff =
  Mr. Psychic. See SABRINA-* in lore-ledger.md.

## Gym 7 — Cinnabar (Blaine, Fire) — Volcano Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD — still the vanilla-count roster, fixed team).
- Levels (tiered, cap 47): Growlithe Lv43 (lead, cap-4), Ponyta Lv45 (cap-2),
  Rapidash Lv45 (cap-2), Arcanine Lv47 (ace, cap).
- Gimmick: canon quiz-door trivia gate, reframed as Blaine testing the MIND before
  the POKéMON (raw power without wisdom is what made a monster). Mechanic unchanged.
- Arc: Blaine helped create MEWTWO at the POKéMON MANSION on Dr. Fuji's team; it broke
  loose and burned everything, and his fire persona / quizzes are his guilt and
  penance. Payoff = a Lab scientist + the Fuji photo + the signed Mansion diary
  fragments. Canon-blend, tag canon-check. See BLAINE-* in lore-ledger.md.

## Gym 8 - Viridian (Giovanni, Ground) - Earth Badge
- Vanilla team: (fill from data)
- Rebalanced team: (TBD — still the vanilla-count roster, fixed team; Earth cap is 63).
- Levels (tiered, cap 50): Rhyhorn Lv46 (lead, cap-4), Dugtrio Lv48 (cap-2),
  Nidoqueen Lv48 (cap-2), Nidoking Lv48 (cap-2), Rhyhorn Lv50 (ace, cap). This is
  the TRAINER_LEADER_GIOVANNI gym fight; his two earlier Rocket boss fights
  (TRAINER_BOSS_GIOVANNI/_2) are separate and unchanged.
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
