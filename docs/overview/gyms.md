# Gyms

One section per gym: leader, type, badge, level cap, team, and puzzle. Tracks our
hard-but-fair rebalance against vanilla.

Level tiering (gym leaders that draw from a pool): the fielded levels are derived
by code from the current level cap at party-build time, so the numbers always
track the cap and a new gym never needs hand-typed levels, only the right tags:
- the ACE-tagged mon (always fielded, sent out last) sits AT the cap;
- the OPENER (slot 0, the first mon sent) sits at cap-4. This holds whether the
  opener is an untagged random draw from the pool (Brock, Lt. Surge, Erika, Koga)
  or a forced LEAD-tagged mon (Misty's Psyduck);
- every other member sits at cap-2.
Whatever levels the mons are authored at in trainers_frlg.party are overridden by
this rule. It applies only to Leader-class trainers that use a pool (poolSize != 0);
non-pool leaders keep their authored levels. The Elite Four / Champion are
excluded on purpose - they keep the levels authored in the data (a graduated climb
toward the Champion, see elite-four.md), NOT the cap. The party is rebuilt fresh at
the start of every battle. Code: CreateNPCTrainerPartyFromTrainer in
src/battle_main.c.

Ace / lead generation (all pool teams): the ACE is always fielded. That is
guaranteed by the `Tags: Ace` mon plus the Bst Match prune, which force-keeps the
ace and picks it for the last slot. A forced lead is OPTIONAL: tag a mon `Tags:
Lead` only when a specific mon must open (Misty's Psyduck); most gyms leave the
opener as a random draw. See how_to_trainer_party_pool.md and src/trainer_pools.c.

Ace held for last (all 8 leaders): `Tags: Ace` only sets party POSITION (the last
slot). It does NOT stop the battle AI from voluntarily switching the ace in early
when it likes the matchup, which made aces (e.g. Brock's Onix) appear second.
Every gym leader now also carries the `Ace Pokemon` AI flag
(`AI_FLAG_ACE_POKEMON`): `IsAceMon` then holds the last-slot mon back until it is
the only one left, so the ace is always the final Pokemon fielded. See
src/battle_ai_switch.c (`IsAceMon`).

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
- Pool members (non-ace all cap-2; ace Onix at cap; no forced lead tag, but the
  opener slot is still dropped to cap-4 by code whichever mon is drawn there.
  Perfect IVs, no EVs, all female except genderless
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
  Ludicolo, Goldeen) and Hydration (Vaporeon).
  Balance pass (per playtest): the strongest coverage was softened toward ~65 BP
  - Scald->Water Pulse, Ice Beam->Icy Wind, Psychic->Psybeam, Giga Drain->Mega
  Drain, Waterfall->Aqua Jet. Two intentional exceptions to the ~65 ceiling:
  GOLDEEN keeps its 80-BP moves (left as-is by request), and CORSOLA keeps
  Sucker Punch (70, priority). All movesets are cap-23 legal (moveset-legality
  skill) EXCEPT Vaporeon's Aurora Beam (see below), kept by request:
  - PSYDUCK (F) LEAD, Swift Swim, Timid (Rain Dance / Water Pulse / Psybeam /
    Aerial Ace) - the story-mandated comic opener, sets rain turn 1.
  - HORSEA (F), Swift Swim, Timid (Rain Dance / Octazooka / Dragon Breath / Icy Wind)
  - BRIONNE (F), Liquid Voice, Timid (Echoed Voice / Rain Dance) - Liquid Voice
    makes Echoed Voice a ramping Water STAB.
  - PYUKUMUKU (F), Innards Out, Timid (Block / Spite / Double Team) - trap-staller;
    Block stops switching, Innards Out dumps its HP into the trapped foe on death.
  - CORSOLA (F), Regenerator, Timid (Water Pulse / Ancient Power / Light Screen / Sucker Punch)
  - LUDICOLO (F), Swift Swim, Timid (Rain Dance / Mega Drain / Water Pulse / Icy Wind)
    - self-sets rain and sweeps at doubled Speed.
  - AZUMARILL (F), Sap Sipper, Jolly (Perish Song / Whirlpool / Bulldoze /
    Aqua Jet) - Whirlpool + Perish Song trap; Sap Sipper walls Grass.
  - GOLDEEN (F), Swift Swim, Naive (Scald / Drill Run / Poison Jab / Icy Wind)
  - VAPOREON (F), Hydration, Timid (Rain Dance / Water Pulse / Aurora Beam / Wish)
    - the wall; Rain Dance + Hydration = status-proof, Wish heals the pool.
    Aurora Beam (65 BP) is above-cap-learnable (level-up L30, no TM/tutor/egg
    path in this build), so it is the one moveset in this gym that is NOT
    cap-legal - kept intentionally as a stronger Ice option than Icy Wind (55).
  - STARMIE (genderless) ACE, Natural Cure, Timid (Water Pulse / Psybeam /
    Shock Wave / Icy Wind) - fast Water-first finisher, always fielded. Coverage
    is deliberately softened from the old Thunderbolt/Ice Beam (BoltBeam) to the
    weaker Shock Wave / Icy Wind so the ace stays water-forward, not a nuke.
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
- Pool members (10; Raichu ace at cap, the other 9 at cap-2; no forced lead tag,
  but the opener slot is still dropped to cap-4 by code. Perfect IVs, no EVs; no
  nicknames).
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
  last). No forced lead tag (Surge-style), but the opener slot is still dropped to
  cap-4 by code whichever mon is drawn there. The other 5 slots are
  BST-matched to the player (POOL_PRUNE_BST_MATCH in src/trainer_pools.c). Perfect
  IVs, no EVs, no nicknames; all mons female (flower-gym flavor). Sun is the pool's
  backbone: six members carry Sunny Day and four more have Chlorophyll to abuse it.
- Levels: cap 35 (`FLAG_BADGE04_GET` row in src/caps.c), derived by code at battle
  time. Vileplume ace at cap (35); the fielded opener at cap-4 (31); every other
  fielded member at cap-2 (33). Pool (ability / nature / moves):
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
- Vanilla team: Koffing Lv39, Muk Lv41, Koffing Lv41, Weezing Lv43 (fixed 4).
- Rebalanced team: a TRAINER POOL of 9 Poison-types that fields 6 (Party Size 6,
  Pool Rules Basic, Pool Prune Bst Match). Venomoth is the ACE (always fielded
  last). No forced lead tag (Surge/Brock model), but the opener slot is still
  dropped to cap-4 by code whichever mon is drawn there. The other 5 slots
  are BST-matched to the player (POOL_PRUNE_BST_MATCH in src/trainer_pools.c).
  Perfect IVs, no EVs, no nicknames. Kept distinct from Erika: pure-Poison +
  Poison/other typings, zero Grass/Poison overlap.
- Levels: cap 50 (`FLAG_BADGE05_GET` row in src/caps.c), derived by code at battle
  time. Venomoth ace at cap (50); the fielded opener at cap-4 (46); every other
  fielded member at cap-2 (48). Pool (ability / nature / moves):
  - VENOMOTH (ace), Tinted Lens, Timid (Bug Buzz / Sludge Bomb / Energy Ball / Psychic)
  - CROBAT, Inner Focus, Jolly (Acrobatics / Cross Poison / U-turn / Roost)
  - MUK, Poison Touch, Jolly (Explosion / Shadow Punch / Poison Jab / Fire Punch)
  - MUK-ALOLA, Poison Touch, Jolly (Knock Off / Poison Jab / Ice Punch / Explosion)
  - WEEZING, Levitate, Timid (Toxic Spikes / Flamethrower / Sludge Bomb / Dark Pulse)
  - DRAPION, Sniper, Jolly (Cross Poison / Night Slash / Earthquake / Aqua Tail)
  - GARBODOR, Weak Armor, Jolly (Gunk Shot / Explosion / Seed Bomb / Drain Punch)
  - SKUNTANK, Aftermath, Naive (Fire Blast / Sucker Punch / Gunk Shot / Poison Gas)
  - SNEASLER, Poison Touch, Jolly (Dire Claw / Drain Punch / Acrobatics / Throat Chop)
- Gimmick: canon invisible-wall maze, reframed - it's a deliberate PROTESTER-
  REPELLENT (petitioners who come to shout at Koga about the smog get lost and give
  up). See KOGA-REVEAL.
- History fragments: see KOGA-* in lore-ledger.md. Hidden layer: Koga is the CEO of
  KOGA INDUSTRIES (Kanto's power utility); the whole Fuchsia area argues over him as
  a necessary evil, and the gym insiders reveal he's a spin doctor. Semi-plain arc.

## Gym 6 — Saffron (Sabrina, Psychic) — Marsh Badge
- Level cap: 53 (`FLAG_BADGE06_GET` row in src/caps.c; see progression.md).
- Vanilla team: Kadabra Lv39, Mr. Mime Lv41, Venomoth Lv41, Alakazam Lv43.
- Structure: a TRAINER POOL of 10 Psychic-types that fields 6 (Party Size 6, Pool
  Rules Basic, Pool Prune Bst Match). Alakazam is tagged the ace (always fielded
  last); no forced lead, so the opener is a random BST-matched draw dropped to
  cap-4 by code. Perfect IVs, no EVs; each runs a +Speed nature that lowers its
  unused attacking stat (Timid on the special attackers, Adamant on the physical
  Contrary Malamar).
- Pool members (non-ace all cap-2; ace Alakazam at cap):
  - ESPEON, Magic Bounce (Psychic / Dazzling Gleam / Mud-Slap / Morning Sun) -
    reflects status and hazards; Mud-Slap answers Steel
  - GOTHITELLE, Shadow Tag (Psychic / Thunderbolt / Signal Beam / Hypnosis) -
    traps the player in; the Shadow Tag + Hypnosis lock is deliberate
  - GARDEVOIR, Synchronize (Moonblast / Psychic / Aura Sphere / Mystical Fire) -
    the widest coverage in the pool
  - HATTERENE, Magic Bounce, Modest (Psychic / Dazzling Gleam / Mystical Fire /
    Nuzzle) - Nuzzle paralyzes fast switch-ins to offset its 29 Speed
  - MR. MIME, Filter (Psychic / Dazzling Gleam / Mystical Fire / Grass Knot) -
    dual STAB plus Steel and Ground coverage
  - XATU, Magic Bounce (Psychic / Air Slash / Heat Wave / Confuse Ray) - annoying
    pivot; Heat Wave for Steel
  - DELPHOX, Blaze (Overheat / Psychic / Laser Focus / Hypnosis) - Laser Focus
    guarantees a crit that ignores Overheat's SpA drop
  - FARIGIRAF, Sap Sipper (Psychic / Hyper Voice / Dazzling Gleam / Earthquake) -
    Normal/Psychic; Earthquake is its only Steel-breaker
  - MALAMAR, Contrary, Adamant (Night Slash / Psycho Cut / Superpower / Hypnosis) -
    Superpower snowballs via Contrary; the pool's lone physical attacker
  - ALAKAZAM, ACE, Synchronize (Psychic / Dazzling Gleam / Shadow Ball / Hypnosis)
    - the canon glass-cannon sweeper
- All movesets are level-cap-legal at 53 (verified with the moveset-legality skill).
- Gimmick: canon teleport-panel maze, reframed as a POSSESSION trial - every trainer
  is forced to fight and gives a contradictory false direction to reach Sabrina; the
  Gym Guide (also possessed) warns "trust no one, not even me." See SABRINA-GYM.
- Arc: she went cold to cage her power and folds the town's minds into her own; losing
  to you makes her LAUGH, breaking the spell and freeing everyone unharmed. Payoff =
  Mr. Psychic. See SABRINA-* in lore-ledger.md.

## Gym 7 — Cinnabar (Blaine, Fire) — Volcano Badge
- Level cap: 58 (`FLAG_BADGE07_GET` row in src/caps.c; see progression.md).
- Vanilla team: Growlithe Lv43, Ponyta Lv45, Rapidash Lv45, Arcanine Lv47.
- Structure: a TRAINER POOL of 8 Fire-types that fields 6 (Party Size 6, Pool
  Rules Basic, Pool Prune Bst Match). Arcanine is tagged the ace (always fielded
  last) and Ninetales is the FORCED LEAD (Tags: Lead, always the opener at cap-4)
  so its Drought sets sun on turn 1 for the whole team. Perfect IVs, no EVs;
  +Speed natures (Jolly on the physical members, Timid on the special attackers,
  Adamant on Talonflame).
- Theme: a SUN team. Ninetales opens with Drought; Skeledirge, Flareon and Rapidash
  each also carry Sunny Day to re-set it. Sun powers every Fire STAB and turns the
  various Solar Beams into no-charge hits. The pool answers Fire's walls
  (Water/Rock/Ground) with Wild Charge, High Horsepower, Earthquake, Solar Beam,
  Energy Ball and Scorching Sands.
- Pool members (non-ace all cap-2; ace Arcanine at cap; forced-lead Ninetales at
  cap-4):
  - NINETALES, LEAD, Drought (Flamethrower / Scorching Sands / Energy Ball /
    Confuse Ray) - the sun-setter and glue
  - HISUIAN ARCANINE, Rock Head (Head Smash / Flare Blitz / Close Combat / Extreme
    Speed) - Rock Head zeroes both nukes' recoil
  - SKELEDIRGE, Blaze (Flamethrower / Shadow Ball / Sunny Day / Solar Beam) - bulky
    and self-sufficient; its own sun makes Solar Beam no-charge
  - FLAREON, Guts (Flare Blitz / Superpower / Quick Attack / Sunny Day) - physical
    wall-breaker; Guts stays dormant without a status source
  - RAPIDASH, Flame Body (Flare Blitz / Wild Charge / High Horsepower / Sunny Day) -
    Flare Blitz is cap-legal via Ponyta's L55 learnup
  - TALONFLAME, Gale Wings, Adamant (Flare Blitz / Acrobatics / Tailwind / U-turn) -
    priority itemless Acrobatics (110 BP) via Gale Wings
  - DARMANITAN, Sheer Force (Flare Blitz / Earthquake / Rock Slide / Iron Head) -
    Sheer Force boosts Rock Slide, Iron Head and Flare Blitz
  - ARCANINE, ACE, Intimidate (Flare Blitz / Close Combat / Wild Charge / Extreme
    Speed) - the canon signature; priority plus wide coverage
- All movesets are level-cap-legal at 58 (verified with the moveset-legality skill);
  Rapidash's Flare Blitz is legal via its pre-evolution (Ponyta learns it at L55).
- Gimmick: canon quiz-door trivia gate, reframed as Blaine testing the MIND before
  the POKéMON (raw power without wisdom is what made a monster). Mechanic unchanged.
- Arc: Blaine helped create MEWTWO at the POKéMON MANSION on Dr. Fuji's team; it broke
  loose and burned everything, and his fire persona / quizzes are his guilt and
  penance. Payoff = a Lab scientist + the Fuji photo + the signed Mansion diary
  fragments. Canon-blend, tag canon-check. See BLAINE-* in lore-ledger.md.

## Gym 8 - Viridian (Giovanni, Ground) - Earth Badge
- Level cap: 63 (`FLAG_BADGE08_GET` row in src/caps.c; see progression.md).
- Vanilla team: Rhyhorn Lv46, Dugtrio Lv48, Nidoqueen Lv48, Nidoking Lv48, Rhyhorn Lv50.
- Structure: a TRAINER POOL of 10 Ground-types that fields 6 (Party Size 6, Pool
  Rules Basic, Pool Prune Bst Match). Nidoqueen is tagged the ace (always fielded
  last) and Hippowdon is the FORCED LEAD (Tags: Lead, always the opener at cap-4) so
  its Sand Stream sets sand on turn 1 for the whole team. Perfect IVs, no EVs. This
  is the TRAINER_LEADER_GIOVANNI gym fight; his two earlier Rocket boss fights
  (TRAINER_BOSS_GIOVANNI/_2) are separate and unchanged.
- Theme: a SAND team, the mirror of Blaine's sun. Hippowdon opens with Sand Stream;
  Marowak, Rhyperior and Nidoking each also carry Sandstorm to re-set it. Sand chips
  the player's non-Ground/Rock/Steel mons, gives Rhyperior +50% SpD, and feeds the
  Sand Force / Sand Veil members. Kangaskhan is a deliberate off-type (Normal) wildcard.
- Pool members (non-ace all cap-2; ace Nidoqueen at cap; forced-lead Hippowdon at
  cap-4):
  - HIPPOWDON, LEAD, Sand Stream, Careful (Earthquake / Crunch / Ice Fang / Slack
    Off) - the sand-setter; bulky and sticky via Slack Off
  - DUGTRIO, Sand Force (Earthquake / Stone Edge / Sucker Punch / Night Slash) - fast
    revenge-killer; Sand Force boosts its Ground/Rock moves in sand
  - MAROWAK, Battle Armor, Adamant (Earthquake / Attract / Sandstorm / Icy Wind) - a
    sand-refreshing annoyer, crit-immune via Battle Armor
  - DONPHAN, Sand Veil, Rash (Earthquake / Seed Bomb / Ice Shard / Stone Edge) - Ice
    Shard priority; wide coverage
  - RHYPERIOR, Solid Rock, Adamant (Earthquake / Stone Edge / Avalanche / Sandstorm) -
    Solid Rock softens its 4x Water/Grass weaks; +50% SpD in sand
  - KROOKODILE, Anger Point (Earthquake / Crunch / Stone Edge / Close Combat) - fast
    dual-STAB attacker with wide coverage
  - GLISCOR, Sand Veil (Earthquake / Acrobatics / U-turn / Roost) - evasive pivot;
    itemless Acrobatics hits 110 BP; Roost recovery
  - NIDOKING, Sheer Force (Earthquake / Poison Jab / Ice Punch / Sandstorm) - Sheer
    Force boosts Poison Jab and Ice Punch; also a sand-refresher
  - KANGASKHAN, Scrappy (Body Slam / Aqua Tail / Icy Wind / Fake Out) - off-type
    Normal wildcard; Scrappy lets Body Slam hit Ghosts
  - NIDOQUEEN, ACE, Sheer Force, Timid (Earth Power / Sludge Wave / Ice Beam /
    Thunderbolt) - a Sheer Force special nuke with BoltBeam coverage
- All movesets are level-cap-legal at 63 (verified with the moveset-legality skill).
- Earlier fights (the recurring arc): his two Rocket-boss battles show the SAME lines
  at a younger evolution stage, with levels fit to the progression CURVE at each story
  beat (near the rival's levels there), NOT to the cap. These are TRAINER_BOSS_GIOVANNI
  / _2 (not pool trainers, so authored levels).
  - Rocket Hideout (post-Erika Lv35, before the Pokemon Tower rival's 34/38; the cap of
    38 is a ceiling, not the curve): DUGTRIO Lv34 (Sand Force), KANGASKHAN Lv35
    (Scrappy), RHYHORN Lv37 (Lightning Rod), a young sand core. Rhyhorn uses Ice Fang
    where its evolved Rhyperior runs Avalanche (Rhyhorn cannot learn Avalanche).
  - Silph Co. (on the Silph rival's curve, ace 52; the cap here is 53 but that is
    Sabrina's gate, not this beat): KANGASKHAN Lv49, NIDOKING Lv50 (Sheer Force),
    RHYDON Lv51 (Lightning Rod), NIDOQUEEN Lv52 ace (Sheer Force). The Nido pair is now
    Moon-Stone-evolved and Rhyhorn has grown to Rhydon; movesets/abilities/natures
    mirror their gym-pool versions at this stage.
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
