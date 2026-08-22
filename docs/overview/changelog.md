# Changelog

Living record of every gameplay/content change vs. vanilla FireRed. Newest first.
Update in the same PR as the change.

## Format
`YYYY-MM-DD` — area — one-line summary (PR/commit ref)

## Entries
- 2026-08-22 - story/surge - NPC fill pass: reflavored 12 vanilla NPCs across
  Vermilion (Mart, Fan Club, House3) and the S.S. Anne (corridors, deck, cabins)
  with Surge's discipline / earned-composure / ship-history lore that builds the
  Captain payoff. Cross-nudges: Mart man + S.S. Anne police agent -> Giovanni
  (faceless boss), Fan Club woman -> Misty. Rocket/Cut/famechecker info preserved
  by appending. Skipped 3 low-fit NPCs to avoid over-saturating the "freedom" beat.
  Lore-ledger SURGE-09..20 added.
- 2026-08-22 - story/brock+misty - NPC fill pass: replaced 19 vanilla flavor NPCs
  with leader lore (Brock 11 across Pewter Museum/Houses/PC/Mart; Misty 8 across
  Cerulean city/PC + Route 25). Subtle and varied, no repeated beats; divorce/
  alimony kept off minors (kids got innocent or coy-only lines). Built-in
  cross-nudges: Museum girl -> Misty, House1 -> Giovanni (Viridian leader away),
  Cerulean policeman -> Giovanni (faceless boss), PC rocker -> Surge. Functional
  hints (CUT, obedience tutorial, famechecker) preserved by appending. Lore-ledger
  rows BROCK-11..21 and MISTY-08..15 added. From the NPC fill lists.
- 2026-08-22 - story/lore - Authored + placed 15 distributed-lore beats for Oak and
  the Elite Four by overwriting existing generic NPCs (no new objects): Oak OAK-05/06/
  07/08/10 (aide gags, dex-rating gremlin, Agatha hook, post-game musing), Lorelei-08
  (Four Island grudge list, "VANILLA"), Bruno-03/04 (Ember Spa mountain sightings),
  Agatha-03/04/08 (young Agatha, Oak goes quiet, post-game reflection), Lance-03/04/05/
  06 (Seven Island Mart + Cinnabar Lab + Oak's Lab "so... a dragon"). OAK-08 and
  AGATHA-08 folded into one post-game Oak branch (FLAG_SYS_GAME_CLEAR). Lore-ledger
  updated per beat. Skipped (need new Porymap objects): OAK-09 (Pallet 3 AM Pidgey,
  no spare townsperson) and LORELEI-06 (Icefall Cave has no NPC objects). Note:
  OAK-07 prepends Oak's recurring dex-rating talk, so it repeats on each mid-game
  Oak chat (broken-record gremlin voice; fire-once would need a spare flag).
- 2026-08-22 - story/rival - Wired Twitch's post-game National-Dex lines and placed
  Buhrito's Pokemon Tower post-battle "Cinnabar" gag (intentional wrong-geography kept).
- 2026-08-22 - story/brock - Placed 4 of Brock's 6 remaining Pewter-arc gossip
  lines by repurposing Pewter's one spare NPC (the Bug Catcher) into a single
  PROGRESSIVE Brock-gossip NPC: ungated "get in line / his lawyers, mostly",
  then FLAG_BADGE01_GET "alimony doesn't pay itself", FLAG_BADGE06_GET "married
  again, connect the dots", FLAG_SYS_GAME_CLEAR "still on the phone, eternal"
  (checked most-progressed-first). Logged as BROCK-03/08/09/10 in the lore-ledger.
  Skipped (no spare female/child NPC without new objects): the "I knew BROCK,
  briefly" woman and the "generous every month" kid (BROCK-03b/03c stay UNPLACED).
  Gym/Museum guides and plot NPCs untouched.
- 2026-08-22 - story/rival - Split the shared rival loss line: Route 22 early now
  has its own Buhrito-voice loss line instead of the Oak's Lab tutorial joke.
- 2026-08-22 - story/rival - Placed Buhrito's dialogue across all 8 rival
  encounters (Oak's Lab, Route 22 early, Cerulean, S.S. Anne, Pokemon Tower,
  Silph Co, Route 22 late, Champion). Buhrito is the default rival (RIVAL_ID_BUHRITO)
  so his lines went into each encounter's non-Twitch default text labels; the Twitch
  branch, teams, and mechanics are untouched. Verbatim from docs/writing/drafts/buhrito.md
  (gen-3 line breaks only). Skipped as unwritten: Pokemon Tower "Cinnabar" post-battle
  gag (pending geo-error call), Champion rematch intro, post-game National-Dex lines.
  Known issue: Text_RivalVictory (player-loss line) is shared by the Oak's Lab tutorial
  loss and the Route 22 early loss, so the Route 22 loss currently shows the tutorial
  joke; splitting it needs a label change (deferred).
- 2026-08-22 - QoL/gameplay - Infinite-repel toggle added to the Start menu
  ("REPEL: ON/OFF"). While ON, all wild encounters are suppressed with zero repel
  consumption (guard in `IsWildLevelAllowedByRepel`, `src/wild_encounter.c`);
  toggled by `FLAG_TOGGLE_NO_ENCOUNTERS` (reclaimed FLAG_UNUSED_0x4A7). Start-menu
  action + dynamic label in `src/start_menu.c`. Fishing and scripted battles are
  unaffected (same as a normal repel).
- 2026-08-22 - intro/story - Wired the new-game intro. Replaced the vanilla Oak
  monologue with a brief author welcome (casual/old-school framing, "play by
  whatever rules you like, the goal is to have FUN and explore") that flows
  straight into the boy/girl + name prompts; the Oak-speech task now skips the
  Nidoran demo (`src/oak_speech.c`, WelcomeToTheWorld -> FadeOutOak). Replaced the
  "this is my grandson" rival-name preamble with the rival-pick framing
  (`gOakSpeech_Text_WhatWasHisName`): the rival is flavored toward your favorite
  opponent, so you choose which. Text in `data/text/new_game_intro_frlg.inc`.
- 2026-08-22 - items/gameplay - Oak's first Poke Ball gift bumped from 5 to 90
  (`PalletTown_ProfessorOaksLab_Frlg`, the Pokedex-handoff gift). The later
  "ran out of balls" top-up still gives 5.
- 2026-08-22 - QoL/config - Confirmed OW_HEAL_AFTER_BATTLE = TRUE (party fully
  heals after every won/ended battle); no change needed, recorded for the overview.
- 2026-08-22 - starters/gameplay - Player starter is now randomized per save. On
  a new game the Oak's Lab starter scene rolls one random Grass, one Water, and
  one Fire starter, each drawn independently from all nine generations (729
  possible trios). The three balls show and give the rolled species; the player
  still picks by type. Rolled once per save (idempotent) and stored in
  `VAR_STARTER_GRASS/WATER/FIRE`. `GetStarterPokemon` is rolled-aware so the
  credits and Champion's Room text name the correct species. Rival starter is
  unchanged. New special `RollRandomStarters` in `src/starter_choose.c`; three
  one-line species swaps in `PalletTown_ProfessorOaksLab_Frlg/scripts.inc`.
  Design spec: `docs/superpowers/specs/2026-08-22-randomized-starters-design.md`.
- 2026-08-22 - trainers/gyms - Rebalanced Lt. Surge (Gym 3, Thunder Badge) from a
  3-mon team into a 10-member Electric TRAINER POOL that fields 6, mirroring
  Brock/Misty (Party Size 6, Pool Rules Basic, Pool Prune Bst Match). Raichu is the
  ACE (always fielded); the other 5 are BST-matched to the player. All members Lv27
  (the Surge cap), perfect IVs, no EVs, no nicknames. Members: Raichu (ace),
  Jolteon, Rotom-Frost, Iron Hands, Hisuian Electrode, Heliolisk, Morpeko,
  Togedemaru, Pincurchin, Pachirisu. +Speed natures except the slow bruisers Iron
  Hands (Brave) and Pincurchin (Quiet). Two off-learnset moves set directly on the
  trainer mons (legal for trainer parties): Rotom-Frost Blizzard, Raichu Extreme
  Speed; every other move is cap-27 legal. Data in `src/data/trainers_frlg.party`
  (`TRAINER_LEADER_LT_SURGE`); overview in `docs/overview/gyms.md`.
- 2026-08-21 - caps/balance - Locked in the hard level-cap ladder to new values in
  `src/caps.c`: Brock 14, Misty 23, Surge 27, Erika 35, Koga 50, Sabrina 53, Blaine
  58, Giovanni 63, Elite Four 72 (Champion onward 100). The Rocket-Hideout-until-Tower
  step (38) is gated on new FLAG_DEFEATED_POKEMON_TOWER_RIVAL, set when the Tower rival
  is beaten (reclaimed FLAG_UNUSED_0x020). Also added the Twitch rival's TPP-team
  trainer entries (`TRAINER_RIVAL_TWITCH_*`) with cap-aligned levels (data only,
  unreferenced until scripts branch on VAR_RIVAL_ID).
- 2026-08-19 - story/flavor - Giovanni "the man who was here all along" self-made
  arc (game-wide). Giovanni is UNIQUE: the recurring antagonist you battle three
  times (Rocket Hideout -> Silph Co -> Viridian Gym) and hear about all game. Hidden
  layer: the ROCKET boss has spent the whole game hiding in plain sight as the absent
  GYM LEADER of Viridian, the sleepy first city; the region carries two absences (an
  unseen boss / a never-there leader) and the player rhymes them until the gym opens
  and canon reveals they are one man. Engine = SELF-MADE MAN FROM THE DIRT (NO son
  thread, decided w/ user): strength is worth, so he built ROCKET from nothing, and
  on losing he gives up the empire to chase strength alone. Reflavored his three
  battle intros/post-battles to escalate the self-made + double-life weight while
  staying hard-but-fair (RocketHideout_B4F, SilphCo_11F, ViridianCity_Gym); added the
  Viridian civic-devotion gag (locked door "away… on business"; Old Man/Woman "a fine
  fellow, I'm sure"; "LEADER returned!"); appended coy "unseen boss / hidden face /
  from nothing" fragments to existing Rocket-beat NPCs (Mt Moon B2F, Rocket Hideout
  B1F, Pokemon Tower 7F, Silph Co 5F/8F/11F, Five Island warehouse); a self-made grace
  note on a Viridian Gym trainer. Reflavored ALL of Giovanni's own lines (no vanilla
  left: three intros/defeats/post-battles, the Earth Badge + Earthquake TM text),
  every Fame Checker Giovanni beat + the letter quote, and all 8 Viridian Gym
  trainers (off vanilla karate/whip filler onto GROUND-grit + reverence for the
  self-made mystery LEADER). GROUND-type through-line (EARTHQUAKE). No son thread:
  both vanilla "red-haired kid" references (Fame Checker + Five Island warehouse)
  reflavored to a self-made-loner note. Text/flavor + appends only, no new objects;
  touches no plot beats; the fights still land. Tag canon-check on the double-life
  fragments. See GIOVANNI-* in docs/writing/lore-ledger.md.
- 2026-08-19 — docs — Added `docs/overview/build-verification.md`, a living
  checklist of merged changes not yet compiled/playtested (web sessions can't
  build and CI has not run on this fork). Covers PRs #2, #4, #5, #6, #9, #10;
  notes the still-open PR #3. No gameplay change.
- 2026-08-19 — story/flavor — Blaine "the man who made the fire" Mewtwo-guilt arc
  (Cinnabar). Reflavored Blaine: the red-hot quiz-master was a lead researcher at the
  POKéMON MANSION on Dr. Fuji's team who helped create MEWTWO; it broke loose, burned
  the mansion, and vanished, and his fire persona is the fire he unleashed. His QUIZ
  gimmick is reframed as testing for wisdom (raw power without judgment made a
  monster), and the guilt leaks in his defeat/badge/TM lines. Coy signed fragments
  beside the canon Mewtwo diary in the Mansion (3F "-F.", B1F "No one asked if we
  should. Forgive me. -B."); a plain-telling payoff from a Lab scientist + the Dr.
  Fuji photo; coy townsfolk lines (he predates the Lab; "some say he lit it"). Canon-
  blend (Adventures-manga flavor, supported by the in-repo Blaine+Fuji photo);
  contradicts no game plot (mansion still burned, Mewtwo still in Cerulean Cave). Tag
  canon-check. Text/flavor only, appended to existing NPCs/journals, no new objects;
  the fight stays red-hot. See BLAINE-* in docs/writing/lore-ledger.md.
- 2026-08-19 — story/flavor — Sabrina "the girl who went cold" possession arc
  (Saffron). Reflavored Sabrina and her gym: she was a sunny child whose psychic gift
  grew past her, so she let her heart go cold and began folding SAFFRON's minds into
  her own (people vanish, feared kept in dolls). Her gym is now POSSESSED, every
  trainer is forced to fight and gives a contradictory false direction to reach her
  (north/south/left/right/still/center/turn-back); defeats are lucid flickers; the
  Gym Guide warns "trust no one here, not even me" (one truth slips: Fighting folds
  to Psychic). Her intro is a cold possessor; on DEFEAT she LAUGHS for the first time
  in years, breaking the spell so the vanished wake unharmed with no memory and no
  grudges. Before/after NPC branches (gated on FLAG_DEFEATED_SABRINA) on the Saffron
  Lass, Worker, Copycat's warm doll, and Mr. Psychic (who warns before and thanks
  after). The Marsh Badge's over-level-disobey mechanic ties to her ("power without a
  warm hand goes cold"). Text/flavor + small script branches only, no new objects;
  touches no plot beats. See SABRINA-* in docs/writing/lore-ledger.md.
- 2026-08-19 — story/flavor — Koga "necessary-evil CEO" ambient lore (Fuchsia +
  bordering routes). Koga's hidden layer: flamboyant CEO of KOGA INDUSTRIES, Kanto's
  power utility, whose poison-gas POKéMON run the refineries (the smog is the price
  of the region's electricity). Necessary evil - the nature town/Safari Zone resent
  him but depend on his power (he even funds half the preserve). The WHOLE area now
  weighs in, spread across stances (pro/dependent, anti/nature, resigned/cynical):
  Fuchsia City (Janine, Old Man, Little Boy, Erik), interiors (House1, House2 fisher,
  Mart Gentleman reflavored as the MAYOR with the balanced view, Safari Office staff
  incl. the funding twist, Warden), the gym insiders who reveal the twist (Kirk =
  spin doctor, Gym Guy = the invisible walls repel protesters, Shawn), Koga's own
  post-battle CEO leak, and Routes 15/18/19 (three stances each). Text/flavor only,
  appended to existing NPCs, no new objects; his battle intro stays archetypal so
  the fight still lands. See KOGA-* in docs/writing/lore-ledger.md.
- 2026-08-19 — story/flavor — Erika "Sleeping Enigma" ambient lore (Celadon +
  beyond). A coy, deliberately-unresolved rumor chorus, appended to existing NPCs;
  no new objects/art; NO plain telling by design. Five contradictory facets hang
  off one anchor (never awake + an impossible garden), poison/medicine dominant
  (~40% of carriers). Celadon City (Little Girl, Woman, Fat Man, Old Man 1 incl. a
  post-`FLAG_BADGE04_GET` wink branch, Rocket Grunts 1 & 2, Boy), Celadon interiors
  (Restaurant drugstore woman, Dept Store 2F/5F, Condominiums tea lady), and gym
  trainer Lisa (the "ask ten of us" aggregator). Fame spreads out of town: Lavender
  grave-keeper + Route 10 (Rock Tunnel mouth) hear the legends. TWO gimmicks: (1)
  the Route 16 bikers fled Celadon in fear of the "perfume/medicine master" and
  camp on the Cycling Road with their POISON types (light no-Celadon-taxes gag);
  (2) the "ladies only" gym is where Brock's "previous sponsors" take refuge (Erika
  hosts, isn't one) - coy, cross-links the Brock arc ("PEWTER number," "let it
  ring"). Rocket lines canon-safe (grunts avoid her garden). See ERIKA-* in
  docs/writing/lore-ledger.md.
- 2026-08-19 — story/flavor — Lt. Surge S.S. Anne arc + gym-gate framing. Rewrote
  the S.S. Anne Captain (`SSAnne_CaptainsOffice_Frlg`): dropped the seasick/back-rub
  gag; reaching the Captain now reads as clearing "the first trial", and he tells
  Surge's history plainly (slums boy, private on the ship, freed the electric
  POKéMON in the hold, drove Rocket from Vermilion, "Not a king. A shield.") then
  awards HM01 CUT. Added coy ambient lore to Vermilion City NPCs (Woman incl. a
  post-`FLAG_BADGE03_GET` "why leader" branch, Old Man 2, Sailor) and S.S. Anne
  crew (Deck Sailor, 1F Corridor Sailor). Text/flavor only, no mechanic change:
  the vanilla Cut-tree already gates the gym (HM01 is only usable once the Captain
  awards it), so the trial framing lives in dialogue, not a new gate object.
  Canon guard: Rocket driven from Vermilion locally only. See SURGE-* in
  docs/writing/lore-ledger.md.
- 2026-08-19 - overworld/HMs - HMs are usable without teaching them to a Pokémon.
  New config flag `OW_HMS_USABLE_WITHOUT_LEARNING` (include/config/overworld.h,
  default TRUE). An HM field move now needs BOTH its Gym Badge AND the HM item in
  the Bag, so beating a Gym is not enough on its own; you must also obtain the
  actual HM. Once you have both, no party Pokémon needs to have learned the move.
  Cut, Rock Smash, Strength, Surf, Waterfall, and Dive trigger by walking into
  the tree/rock/water as usual and your lead Pokémon performs them
  (`src/scrcmd.c` checkfieldmove fallback, `src/field_control_avatar.c` surf
  trigger). Fly and Flash, which have no obstacle to interact with, appear in any
  Pokémon's party menu when you have the Badge and hold the HM and are somewhere
  the move applies (outdoors for Fly, an unlit cave for Flash) in
  `src/party_menu.c`. Badge-only gating (must know the move) still applies when
  the flag is off (upstream behavior). Core gate lives in `src/field_move.c`
  (`IsHMUnlocked`) with the HM item recorded per move in `include/field_move.h`.
  Verify in-game: with the Cascade/Boulder-era Badge earned and HM01 in the bag
  but no Cutter, a cuttable tree still prompts CUT; lacking the HM (or the Badge)
  it does not. Does not touch Teleport, Dig, Sweet Scent, Soft-Boiled, or Secret
  Power.
- 2026-08-19 — caps/menu — Turned on hard level caps and added free, cap-limited
  menu leveling. `include/config/caps.h`: `B_EXP_CAP_TYPE = EXP_CAP_HARD`,
  `B_LEVEL_CAP_TYPE = LEVEL_CAP_FLAG_LIST`, `B_RARE_CANDY_CAP = TRUE`. Over-cap
  mons now gain 0 battle EXP and Rare Candy is blocked at the cap, using the
  badge-gated Kanto cap table already in `src/caps.c`
  (15/19/24/29/31/33/42/46/58). The field party menu gains a `LEVEL` option
  (opens `LEVEL UP` / `LEVEL TO CAP`) that raises a mon for free but never past
  the current cap, reusing the Rare Candy level-up/move-learn/evolution pipeline
  (`src/party_menu.c`, `src/data/party_menu.h`).
- 2026-08-19 — QoL — Auto-heal after battle. New config flag `OW_HEAL_AFTER_BATTLE`
  (include/config/overworld.h, default TRUE) fully restores the party (HP, status,
  PP) after every won/ended wild, trainer, rematch, and scripted/legendary encounter,
  removing Pokémon Center trips. Excludes battle facilities (Frontier, Trainer
  Tower/Hill), link, Safari, recorded, and tutorial battles. Trade-off: removes
  battle-to-battle attrition as a difficulty lever. Verify in-game: after a normal
  wild/trainer fight the party is full HP/status/PP; inside Trainer Tower it is not.
- 2026-08-19 — config — EVs disabled game-wide. Player mons gain no EVs from
  battle (`B_EV_CAP_TYPE = EV_CAP_NO_GAIN`) or from vitamins/EV items
  (`B_EV_ITEMS_CAP = TRUE`) in include/config/caps.h; also fixed a malformed
  duplicate `B_EV_CAP_VARIABLE` define there. Removed the leftover EV spreads
  from the double-battle ally (src/data/battle_partners.party). Real trainers
  and gym leaders already had no EVs; debug_trainers.party left untouched.
- 2026-08-17 — setup — Project scaffolded from rh-hideout/pokeemerald-expansion
  (fork SevLuc/pokeemerald-expansion), FireRed target, CLAUDE.md + docs/ created.
  No gameplay changes yet; all config at expansion defaults.
