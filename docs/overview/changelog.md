# Changelog

Living record of every gameplay/content change vs. vanilla FireRed. Newest first.
Update in the same PR as the change.

## Format
`YYYY-MM-DD` — area — one-line summary (PR/commit ref)

## Entries
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
  note on a Viridian Gym trainer; and aligned Fame Checker beat 0 to the self-made
  framing. GROUND-type through-line (EARTHQUAKE). Vanilla "red-haired kid" gag left
  untouched (no son arc). Text/flavor + appends only, no new objects; touches no plot
  beats; the fights still land. Tag canon-check on the double-life fragments. See
  GIOVANNI-* in docs/writing/lore-ledger.md.
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
