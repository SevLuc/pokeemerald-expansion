# Changelog

Living record of every gameplay/content change vs. vanilla FireRed. Newest first.
Update in the same PR as the change.

## Format
`YYYY-MM-DD` — area — one-line summary (PR/commit ref)

## Entries
- 2026-08-27 - feature/rental - Draft foundation (M3, no UI yet). Added
  include/rental_mode.h + logic in src/rental_mode.c for the draft: an in-RAM
  `gRentalRun` state (offer of 12, roster of 6, format, restricted cap, bring
  count), `GenerateRentalOffer` (rolls 12 distinct-species / distinct-item sets
  with at most `cap` restricted, so any 6 picked are already clause- and cap-legal),
  and `RentalRoster_TryAdd`/`Remove` with full Species+Item-clause + cap checks.
  Pure logic, no graphics; the Battle Factory select screen is adapted on top of
  this next (developed in the build loop). In-RAM only (persistence deferred). Not
  yet compiled/ROM-tested (web session).
- 2026-08-27 - feature/rental - Rental data-proof in the hub (M2 slice 3). Added
  src/rental_mode.c with a `BufferRandomRentalMon` script special (registered in
  data/specials.inc) that picks a random set from the generated `gRentalMons` pool
  and buffers its species + first move name. Repointed the Battle Tower Lobby's
  Singles attendant (map.json) to a new `EventScript_RentalAttendant` that shows
  them in a message box, proving the M0 data pipeline is live in-game. NOTE: this
  is a data-proof, not a battle. The actual rental battle is deferred to M3, where
  the draft feeds mons into the Battle Tower's own tested battle pipeline instead of
  a hand-rolled one (safer, and testable incrementally). Name/gender pick also
  deferred (low value for the skeleton). Not yet compiled/ROM-tested (web session).
- 2026-08-27 - feature/rental - Rental battle mode entry (M2 slice 1, scaffolding).
  Added `CB2_StartRentalMode` (src/overworld.c), which mirrors `CB2_NewGame` but
  warps the player into the Battle Tower Lobby (reused as the rental hub) instead
  of the story start. It sets up an in-RAM game state only and NEVER writes to
  flash, so a story save on the cartridge is never touched. Temporarily launched by
  pressing R on the main menu (src/main_menu.c) to validate the boot; the polished
  "RENTAL BATTLE" menu row and the name/gender pick + stub battle come in later
  slices. No save-system changes. Not yet compiled/ROM-tested (web session).
- 2026-08-27 - QoL/config - Hidden Power (and other dynamic-type moves) now show
  their REAL type everywhere a move is viewed. Set `P_SHOW_DYNAMIC_TYPES = TRUE`
  in include/config/pokemon.h (was FALSE/vanilla). The summary screen move list
  and the in-battle move-select window already compute the true type via
  `CheckDynamicMoveType` when this flag is on, so Hidden Power reads as its
  IV-derived type with the matching type-colored badge instead of always
  "Normal". Global (main game too), display-only, no battle-mechanics change.
  Groundwork for the rental battle mode's move scouting (M1 of the Phase 1 plan).
  Config-only; verify on the Mac build that a Hidden Power mon's summary shows the
  real type badge. (PR: rental mode M1)
- 2026-08-26 - QoL/config - Enabled follower Pokemon (HGSS style). Set
  `OW_FOLLOWERS_ENABLED = TRUE` in include/config/overworld.h. The lead party
  Pokemon now walks behind the player, spawning automatically on map load
  (UpdateFollowingPokemon), emerging from its actual stored Poke Ball
  (OW_FOLLOWERS_POKEBALLS already TRUE), bobbing during idle/walk
  (OW_FOLLOWERS_BOBBING already TRUE); pressing A gives a built-in reaction from
  data/scripts/follower.inc. Prerequisite OW_POKEMON_OBJECT_EVENTS was already
  TRUE, and no species/level/location restrictions are set (all mons may follow).
  Pure flavor, no mechanical/battle impact. Config-only, not yet compiled/
  ROM-tested (web session). Caveat: special scripted scenes may later need the
  follower suppressed via B_FLAG_FOLLOWERS_DISABLED; none handled yet (address
  if a scene looks wrong in playtest).
- 2026-08-26 - QoL/config - Made all TMs reusable. Set `I_REUSABLE_TMS = TRUE`
  in include/config/item.h (Gen5-8 behavior): a TM is no longer consumed on use,
  so each one bought or found can be taught to any number of Pokemon forever.
  Serves the hard-but-fair goal (players can freely optimize movesets to meet
  tuned fights) at the cost of removing TM scarcity as an economy lever. Shop TM
  purchases become effectively one-time. Config-only, not yet compiled/ROM-tested
  (web session).
- 2026-08-25 - content/e4-agatha - Rebuilt Elite Four Agatha as a 14-mon Ghost +
  Poison draw pool (fields 6, BST-matched), ace Gengar (Cursed Body). Reframes the
  canon gen-1 roster (Gengar/Golbat/Haunter/Arbok) as a disruption-heavy pool
  (Confuse Ray / Will-O-Wisp / Spore / Strength Sap) around hard-hitting Ghosts:
  Polteageist, Mismagius, Dusknoir, Dragapult, Mimikyu, Chandelure, Drifblim,
  Basculegion, Dhelmise + Crobat, Amoonguss, Dragalge, Sneasler. Added Agatha's
  slot spread {63,64,64,65,65,66} to GetEliteFourPoolSlotLevels (src/battle_main.c).
  All movesets legality-checked; party data validated with the trainerproc tool.
  Note: Gengar's ability here is Cursed Body, not Levitate (P_UPDATED_ABILITIES).
  Not yet compiled/ROM-tested (web session). Docs: overview/elite-four.md.
- 2026-08-25 - balance/banned-moves - Banned Substitute for the player. Added
  MOVE_SUBSTITUTE to src/data/banned_moves.h (now 77 moves), so no player-owned or
  wild Pokemon can carry it via level-up, evolution, egg, TM, tutor, the Move Relearner,
  capture, gifts, or static encounters (CanLearnTeachableMove and ApplyPlayerMoveBans
  gate every path). Trainers are unaffected and still use it, per the banned-moves
  design. Also removed the now-dead dedicated Substitute move tutors, whose only move
  is now unlearnable: the Fuchsia City tutor (FRLG, src/scripts + FuchsiaCity_Frlg map
  NPC + its text) and the Lilycove Dept. Store rooftop tutor (Emerald equivalent).
  Substitute stays a defined, fully functional move. Docs: overview/banned-moves.md
  updated (moved out of "kept legal", counts bumped); test added in test/banned_moves.c.
- 2026-08-25 - content/e4-bruno - Rebuilt Elite Four Bruno as a 17-mon Fighting +
  Steel draw pool (fields 6, BST-matched), ace NamasteNiffo (Machamp, No Guard).
  Reflavored from pure-Fighting to "fists of steel": Fighting core + a Steel core
  (Gholdengo/Magnezone/Empoleon/Bronzong/Ferrothorn/Togedemaru/Steelix) + Sandslash.
  All movesets legality-checked. Added GetEliteFourPoolSlotLevels (src/battle_main.c)
  so E4 pools take per-SLOT fielded levels (lead..ace) instead of snapping to cap:
  Bruno 61/62/63/63/63/65, and Lorelei onto her planned 60/61/61/61/61/63. Party
  data validated with the trainerproc tool. Not yet compiled/ROM-tested (web session).
- 2026-08-25 - content/economy - Set every Celadon Game Corner prize to cost 1 coin.
  All prize costs in the prize room (Pokemon, TMs, and battle items) were changed to
  1 coin, and the price labels in the exchange menus (src/data/script_menu.h) were
  updated to match ("1 COIN"). Covers both FireRed and LeafGreen prize tables.
- 2026-08-25 - content/trainers - Added Aurorus to Lorelei's Elite Four snow pool
  (TRAINER_ELITE_FOUR_LORELEI), bringing it to 12 candidates that field 6. Lv72,
  Refrigerate, Modest, Hyper Voice / Discharge / Earth Power / Hyper Beam (all
  cap-legal at 72; Refrigerate turns both Hyper Voice and Hyper Beam into boosted
  Ice STAB, giving Ice/Electric/Ground coverage). NOTE: as a Refrigerate attacker
  Aurorus is a non-setter, so it raises the pool's non-setter count to 5 and the
  hard "a snow-setter is always fielded" guarantee no longer strictly holds (give
  it a Snowscape move to restore it). Docs: overview/elite-four.md updated (pool
  count, snow-lead rule, weakened-guarantee note, member list).
- 2026-08-25 - content/trainers - Filled Giovanni's two earlier Rocket-boss fights
  (TRAINER_BOSS_GIOVANNI / _2) to mirror his gym sand pool at a younger evolution
  stage, with levels fit to the progression curve at each story beat (near the local
  rival's levels), not to the cap. Rocket Hideout (post-Erika Lv35, before the Tower
  rival's 34/38): Dugtrio Lv34, Kangaskhan Lv35, Rhyhorn Lv37 (Rhyhorn runs Ice Fang
  since it cannot learn Rhyperior's Avalanche). Silph Co. (on the Silph rival's curve,
  ace 52): Kangaskhan Lv49, Nidoking Lv50, Rhydon Lv51, Nidoqueen Lv52 ace, the Nido
  pair now Moon-Stone-evolved and Rhyhorn grown to Rhydon. Perfect IVs;
  abilities/natures/movesets match their gym versions at each stage (Rhyhorn/Rhydon use
  Lightning Rod since pre-Rhyperior forms lack Solid Rock). All movesets verified
  against each species' legal pool. Docs: overview/gyms.md.
- 2026-08-25 - content/trainers - Converted Gym 8 Giovanni (Ground, cap 63) to a
  trainer pool, replacing his vanilla 5-mon roster in trainers_frlg.party. Fields 6
  of a 10-Ground pool, ace Nidoqueen (Tags: Ace, Sheer Force special nuke) with
  Hippowdon as forced lead (Tags: Lead) so Sand Stream opens a sand team (mirror of
  Blaine's sun; Marowak/Rhyperior/Nidoking carry Sandstorm to refresh it). Kangaskhan
  is a deliberate off-type Normal wildcard. Party Size 6 / Pool Rules Basic / Pool
  Prune Bst Match, perfect IVs, +Speed/relevant natures. Only TRAINER_LEADER_GIOVANNI
  (the gym fight) changed; his Rocket-boss fights (TRAINER_BOSS_GIOVANNI/_2) are
  untouched. All movesets verified level-cap-legal with the moveset-legality skill.
  Docs: overview/gyms.md.
- 2026-08-25 - content/trainers - Built pool teams for Gym 6 Sabrina (Psychic, cap
  53) and Gym 7 Blaine (Fire, cap 58), replacing their vanilla 4-mon rosters in
  trainers_frlg.party. Sabrina fields 6 of a 10-Psychic pool, ace Alakazam (Tags:
  Ace); Blaine fields 6 of an 8-Fire pool, ace Arcanine (Tags: Ace) with Ninetales
  as forced lead (Tags: Lead) so Drought opens a sun team. Both use Party Size 6 /
  Pool Rules Basic / Pool Prune Bst Match, perfect IVs, +Speed natures. All movesets
  verified level-cap-legal with the moveset-legality skill (Rapidash's Flare Blitz is
  legal via Ponyta's L55 pre-evo learnup). Docs: overview/gyms.md.
- 2026-08-25 - content/npc-flavor - Kanto vanilla-NPC fill pass: reflavored 161
  not-yet-flavored flavor NPCs (177 text blocks) across 23 Kanto maps in the
  slight-nudge / show-dont-tell doctrine. Seeded 10 new distributed world-threads
  (WT-01..WT-10 in lore-ledger.md: chalk arrows, hand-carved Poke Balls dying to
  Silph, bolder wilds, the culvert-coin ritual, the empty-belt Walker, the
  Vermilion/Cinnabar ferry feud, the Clefairy full-moon descent, Rock Tunnel's
  unlit lamps, naming Pokemon by their cry, and the Pallet box legend) onto their
  dispersed carriers; every other NPC got standalone town-character flavor. Sevii
  Islands and all functional / plot / tutorial / pet-Pokemon NPCs left vanilla on
  purpose. WT-10's post-Elite-Four payoff is placed on Pallet's existing Sign Lady
  (legend pre-clear, payoff after FLAG_SYS_GAME_CLEAR via a goto_if_set branch); no
  NPC added. Review: docs/writing/fill-pass-2026-08-kanto.md. No .pory maps affected.
- 2026-08-24 - balance/trainers - Gym-leader pool teams now derive their fielded
  levels from the current level cap at battle time instead of relying on hand-typed
  levels in trainers_frlg.party: the `Tags: Ace` mon sits at the cap, the opener
  (slot 0) at cap-4, and every other member at cap-2. Applies to Leader-class
  trainers that use a pool (Brock/Misty/Surge/Erika/Koga and any future gym); the
  Elite Four / Champion are excluded and keep their authored (graduated) levels, and
  non-pool leaders keep theirs too. Ace generation is already guaranteed by the
  `Tags: Ace` mon plus the Bst Match prune; a forced lead stays optional via
  `Tags: Lead`. Code: CreateNPCTrainerPartyFromTrainer (src/battle_main.c),
  `isPoolGymLeader` gate. Test: test/battle/trainer_control.c ("... tiers fielded
  levels off the level cap ..."). Docs: overview/gyms.md, overview/elite-four.md.
- 2026-08-24 - feature/trainers - Added a per-Pokemon `Status:` field to the
  `trainers.party` format so a trainer's mon can enter battle already afflicted.
  Extends trainerproc (parse + emit), adds `u32 status` to `struct TrainerMon`
  (include/data.h), and applies it via SetMonData in CreateNPCTrainerPartyFromTrainer.
  Written verbatim as a `STATUS1_*` C expression, e.g. `Status: STATUS1_FREEZE` or
  `Status: STATUS1_SLEEP_TURN(3)`. Distinct from the trainer-level "Starting Status"
  (field effects). Docs added to trainers.party header.
- 2026-08-24 - content/rival - Filled in Buhrito's teams for ALL seven rival
  encounters (his ace is the Elekid line; nicknames are capitalized). Oak's Lab:
  Electafart (Elekid) Lv5. Route 22 early: 5 mons Lv9 with a self-sabotage pre-status
  gag (Hoothoot preslept but Insomnia wakes it, Shroomish pre-frozen, Skitty preslept,
  Magikarp with only Splash). Cerulean: 6 mons Lv18-21. S.S. Anne: 6 mons Lv23-26 (ace
  evolves to Electabuzz). Pokemon Tower: 6 mons Lv34-38. Silph Co: 6 mons Lv46-49
  (Golem/Alakazam/Snorlax/Milotic/Magneton/Lapras). Route 22 late rematch: 6 mons
  Lv56-61 (Ludicolo/Golem/Dragonite/Hitmonchan/Whiscash + Electabuzz ace). Champion
  first fight: 6 mons Lv67-72 (ace @ Sitrus Berry, keeps the 4 Full Restores + mugshot).
  Same team written to all three starter-variant constants per fight. Early teams run
  level-up-legal sets; later teams also use standard TM/tutor moves. overview/trainers.md
  updated. (Champion REMATCH still TODO.)
- 2026-08-23 - fix/field - Repel start-menu toggle no longer hard-locks. It set
  gMenuCallback to its own callback but never restored the input handler, so the
  callback re-ran every frame and flipped the flag ~60x/sec. Now resets
  gMenuCallback = HandleStartMenuInput after one toggle (src/start_menu.c).
- 2026-08-23 - balance/gyms - Gym leaders & Elite Four now always open with a mon
  4 levels under their current level cap. Applied by code (slot 0 in
  CreateNPCTrainerPartyFromTrainer, src/battle_main.c) for any Leader/Elite-Four
  class trainer, so the cap-4 opener holds even when the pool leads with an
  untagged random mon (Brock, Lt. Surge) - no Lead tag needed. Ace still sits at
  the cap and closes; other members stay cap-2 from the data. Champion excluded.
- 2026-08-23 - rival/dialogue - Locke is now a fully playable 3rd rival identity.
  Added RIVAL_ID_LOCKE (=2) and the "LOCKE" pick-menu option + flavor blurb
  (src/oak_speech.c, data/text/new_game_intro_frlg.inc, include/constants/vars.h,
  include/event_scripts.h). Wired his full battle dialogue (intro/defeat/post, plus
  victory lines on the earlyrival beats) across all rival encounters via
  goto_if_eq VAR_RIVAL_ID, RIVAL_ID_LOCKE branches that KEEP the vanilla per-starter
  split and reuse the vanilla rival trainer ids: Oak's Lab, Route 22 early, Cerulean,
  S.S. Anne, Pokemon Tower, Silph, Route 22 late, Champion (7 map scripts.inc). Voice
  is the warm "Documentarian" streamer-homage (docs/writing/drafts/locke.md). ALSO
  gated the runtime-generated nuzlocke team to the Locke identity only
  (ShouldGenerateLockeParty = VAR_RIVAL_ID == RIVAL_ID_LOCKE), so the default rival
  (Buhrito) reverts to its vanilla static teams; Twitch unaffected. Deferred: Locke
  lines for the Champion rematch and a few non-battle rival slots (Oak's Lab parcel
  scene, Silph pre-approach) still fall through to the default rival's text.
- 2026-08-23 - intro/rival - The "received X from Oak" line in Oak's Lab now names the
  rival's starter by identity instead of always the vanilla type-counter (which showed
  e.g. "Squirtle"): Twitch always Charmander, Buhrito always Elekid; any other identity
  (a future Locke) keeps the variable type-counter species. Only the displayed name
  changes - the removed ball object and the battle party are untouched.
  data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc.
- 2026-08-23 - config/battle - New games now default the battle style to SET (was
  SHIFT). src/new_game.c.
- 2026-08-23 - ui/summary - Skills (stats) page: press A to toggle the six stats
  between actual values and IVs, shown as raw 0-31 numbers. Config-only via
  P_SUMMARY_SCREEN_IV_EV_INFO / P_SUMMARY_SCREEN_IV_ONLY / P_SUMMARY_SCREEN_IV_EV_VALUES
  in include/config/summary_screen.h.
- 2026-08-23 - battle/balance - Disabled B_AFFECTION_MECHANICS (include/config/battle.h).
  Caught Pokemon start at max friendship (for instant friendship evolutions); with
  affection on, that silently gave the player's mons +2 crit stage (near-constant
  "A critical hit!") plus hidden dodge / survive-a-hit / damage-reduction / self-cure
  buffs. Friendship evolutions are unaffected by this flag.
- 2026-08-23 - field/heal - Auto-heal-after-battle now also fires on the early-rival
  WIN path, so the party heals after the Oak's Lab first fight and the Route 22 early
  rival fields (previously only wild and normal-trainer battles healed). src/battle_setup.c.
- 2026-08-23 - encounters - Added a wild grass table to Pewter City, a 5th pre-Brock
  grass area (Lv5-8): Anorith, Lileep, Cranidos, Elekid, Glimmet, Growlithe,
  Growlithe-Hisui, Mienfoo, Rufflet, Shieldon, Spinda, Amaura (fossil/rock flavor).
  gen_encounters.py gains a --only freeze mode so a new map can be filled without
  reshuffling existing tables. tools/gen_encounters.py, src/data/wild_encounters.json,
  docs/overview/encounters.md. Tall-grass metatiles (0x0D) were painted into the
  fenced flower garden's interior lawn (Pewter tiles x27-35, y26-29; enterable via the
  bottom gap at x31,y30), so the table triggers in-game.
  data/layouts/PewterCity_Frlg/map.bin.
- 2026-08-23 - trainers/gyms - Gym leader teams now tier their levels instead of
  fielding a whole team at the cap. Only the ACE sits at the level cap; the bulk
  sit at cap-2, and a forced LEAD (Misty's Psyduck) sits at cap-4. Pool gyms with
  no LEAD tag (Brock, Lt. Surge) get no cap-4 member (an untagged mon is not
  guaranteed to be drawn), so every non-ace pool member is cap-2. Applied to all 8
  gyms in src/data/trainers_frlg.party: Brock (ace 14, rest 12), Misty (ace 23,
  lead 19, rest 21), Lt. Surge (ace 27, rest 25), Erika (29/27/25), Koga
  (43/41/39), Blaine (47/45/43), Sabrina (43/41/39), Giovanni gym/TRAINER_LEADER
  (50/48/46). Aces and their caps unchanged; only non-ace members moved (a slight
  net-easier tweak). Giovanni's two Rocket boss fights left untouched. gyms.md
  updated.
- 2026-08-23 - trainers/rival - Locke (the default, non-Twitch rival) now plays
  nuzlocke-style: his party is GENERATED at battle time instead of read from a static
  entry. A per-save seed (two event vars, rolled once at new game) drives it, so each
  playthrough gets a different but consistent team and the same save always rebuilds
  the same one. Applies to every Locke fight EXCEPT Oak's Lab (that keeps the static
  starter-only tutorial team); Route 22 early fields 4 mons, Cerulean onward field 6.
  His starter (the type that counters the player's, encoded by which of the three
  trainer-id variants runs) is always on the team but NEVER leads; slot 0 is the
  least-weak mon (fewest type weaknesses). Non-starter mons are rolled one per visited
  area from that area's wild table (land/water/fishing) in a fixed story order, no
  duplicate species, each evolved to its level-appropriate stage; when the area pool
  exceeds team size, members are picked for type coverage (resist the starter's
  weaknesses, minimize shared team weaknesses). Levels match the vanilla rival ace per
  fight (12/18/20/25/40/53/63, rematch 75). The Twitch rival is unaffected. Code in
  src/rival_nuzlocke.c, include/rival_nuzlocke.h, src/data/rival_nuzlocke_battles.h;
  hooked in CreateNPCTrainerParty (src/battle_main.c). Overview in
  docs/overview/trainers.md.
- 2026-08-23 - intro/rival - Rival pick now shows a per-rival flavor blurb before
  the YES/NO confirm (Oak speech). Blurbs indexed by VAR_RIVAL_ID via
  sRivalFlavorText[] in src/oak_speech.c; strings in
  data/text/new_game_intro_frlg.inc (Buhrito, Twitch, Locke). Locke's encounters
  not yet wired; missing/OOB index falls back to the generic confirm line. Built
  clean on Mac.
- 2026-08-23 - trainers/elite-four - Wired Lorelei's Ice pool into
  src/data/trainers_frlg.party (11 members, fields 6 via Party Size 6 + Bst Match,
  Lapras ace). Added a new `POOL_PICK_SNOW_LEAD` pick function
  (include/trainer_pools.h, src/trainer_pools.c): leads with a Snow Warning mon
  (Alolan Ninetales) if fielded, else a Snowscape carrier, so Snow is up turn 1
  regardless of the BST-matched draw. Ninetales is not force-kept (stays a normal
  candidate). Test added in test/battle/trainer_control.c. Not yet compiled
  (web session); build + playtest on Mac.
- 2026-08-23 - trainers/elite-four - Drafted Lorelei's Ice draw pool (11 members,
  all Lv72 cap-legal: abilities, natures, movesets) built around modern Snow.
  Alolan Ninetales is the preferred Snow lead with a conditional fallback (a
  Snowscape carrier leads if she is not fielded); Lapras is the ace. New doc
  docs/overview/elite-four.md; trainers.md Lorelei row updated. Fielded subset,
  pool wiring, and the conditional-lead rule in src/trainer_pools.c are TODO.
- 2026-08-23 - trainers/rival - Placed the Twitch rival teams on the trainer curve
  (cap-1 top for crit-path fights, only leaders hold the cap). Cerulean 23->22,
  S.S. Anne 27->26 (whole teams -1); Silph 50->52 (whole team +2). Oak's Lab (5,
  tutorial), Route 22 early (13, cap-1), Pokemon Tower (38, gate), Route 22 late
  (63, E4-split floor) and Champion (72, capstone) unchanged. VAR_RIVAL_ID branches
  were already wired. (src/data/trainers_frlg.party; progression json regenerated)
- 2026-08-23 - mechanics/moves - Player-only banned moves. 76 moves (all setup,
  Protect/Detect stall family, Toxic + Will-O-Wisp, entry hazards, and key utility:
  Baton Pass, Destiny Bond, Trick Room, Tailwind, Whirlwind/Roar, Leech Seed,
  Trick/Switcheroo/Bestow, Spite, Mind Reader/Lock-On) are stripped from player and
  wild Pokemon; TRAINERS keep them (auto-moveset path untouched). When a banned move
  sits in a species' level-up learnset, the player's mon gets a curated same-type egg
  move instead (1336 mapped), else backfills its other legal level-up moves (831).
  Enforced on capture/gift/starter/fossil/egg-hatch, level-up + evolution learning,
  TM/tutor, and the Move Relearner. New: src/data/banned_moves.h, test/banned_moves.c;
  hooks in pokemon.c, wild_encounter.c, script_pokemon_util.c, daycare.c,
  move_relearner.c. Full list + rationale in docs/overview/banned-moves.md.
- 2026-08-23 - encounters/region-wide - Rebuilt every wild encounter table via
  `tools/gen_encounters.py`. Base forms only (family roots); all kept roots
  (192 land + 41 water) catchable before the E4. Equal chance per slot; fishing
  authored in slots 5-9 with Surf water_mons matched (per the master fishing-code
  convention) so all rods + Surf yield the same fish; vanilla level bands kept.
  Difficulty tiered by effective BST per split (level cap + item access, items at
  Erika). LeafGreen mirrored. Overview regenerated. (design: docs/design/encounter-tables.md)
- 2026-08-23 - trainers/AI - Gave every non-Twitch trainer the Try To Faint AI flag.
  543 regular trainers went from `Check Bad Move` to `Check Bad Move / Try To Faint`
  (includes the two early Giovanni/Omega boss fights, which are no longer AI-light).
  Gym leaders, Elite Four, Champion+rematches and the Buhrito rival already ran the
  full `Check Bad Move / Try To Faint / Check Viability` (unchanged). The Twitch rival
  (`TRAINER_RIVAL_TWITCH_*`) keeps RANDOM AI (no AI line) as a TPP homage. Data only,
  src/data/trainers_frlg.party.
- 2026-08-23 - trainers/coverage - Relocated the ~30 high-BST FINAL evolutions that
  the coverage pass had to leave in segments 2-6 (no late themed trainer existed for
  their type) onto LATE (seg 7-9) trainers, so they appear at believable levels
  (host levels 53-67). Rethemed 12 late generic trainers (Ghost/Bug/Dragon/Fighting
  Swimmers in seg7; Dark/Rock/Psychic/Fighting Cooltrainers + a Pokemaniac in seg
  8-9) and backfilled each vacated early slot with an on-theme, level-appropriate,
  already-used species. Invariant preserved: all 528 kept species still appear >=1;
  60 slots edited across 35 trainers. Plan in docs/data/reroll/relocate.json.
  Caveats: needed 12 retheme trainers (not fewer) because late generic trainers have
  very few duplicate-backed slots to safely displace; 5 of them are Water Swimmers
  now fielding non-Water finals, which is thematically loose for Kanto-authentic feel
  (revisit if it bothers). Build verified (make firered).
- 2026-08-23 - pokemon/pool - Added all five Rotom appliance forms to the kept pool
  (Rotom-Heat Electric/Fire, Rotom-Wash Electric/Water, Rotom-Frost Electric/Ice,
  Rotom-Fan Electric/Flying, Rotom-Mow Electric/Grass; each BST 520). Base Rotom
  was already in. Recorded in docs/data/kept-pokemon-stats.csv and the Electric/
  Ghost entry of docs/overview/encounters-candidates.md.
- 2026-08-23 - trainers/coverage - Coverage pass so EVERY kept-pool species (528
  incl. Rotom forms) now appears on at least one trainer. Was 183 unused -> 0.
  Reassigned 184 slots across 119 trainers, always replacing an OVER-used duplicate
  (BST window relaxed for this pass; nothing dropped to zero). Finals/pseudo-legends
  placed in late segments (7-9). Added the two missing trainer THEMES by rethemeing
  whole teams: Dragon x4 and Ice x4 trainers (Cooltrainer/Scientist/Picnicker/Camper/
  Lass classes across segs 3/6/7), plus 1 Steel and 1 Rock retheme. All 11 legendaries
  (Flutter Mane, Iron Bundle, Kubfu, both Urshifu, all 6 Rotom forms) placed on
  seg7-9 matching-type trainers. Over-spikes shrank (Butterfree 20->12, Sharpedo
  13->5, Electabuzz 10->4). Plan in docs/data/reroll/coverage.json; data in
  src/data/trainers_frlg.party. Caveat: Rock/Steel/Ghost/Bug have no late-segment
  themed trainers, so ~30 of their high-BST finals sit in segs 4-6 rather than 7-9
  (flagged per-mon in coverage.json). Build verified (make firered).
- 2026-08-23 - trainers/teams - Rerolled every GENERIC trainer's team across all 9
  segments (special characters - gym-leader pools, rivals, Giovanni, Elite Four,
  Champion, twitch variants - untouched). Each trainer keeps its team SIZE; species
  are drawn only from the kept encounter pool, matched to lore/type (class-locked
  like Bug Catcher->Bug; gym-map trainers use the gym type; generic classes themed
  from their dialogue). RULES: pick a base species whose BST is within [origBST,
  origBST+50] (equal-or-stronger only, nearest-tight upper widen when a band is
  sparse), THEN auto-evolve it to its level-appropriate form using LEVEL-UP
  evolutions only (so a Lv18 Caterpie becomes a Lv18 Butterfree; friendship/beauty/
  item/trade evos do NOT auto-fire). Levels follow the per-split ramp. Rerolled mons
  use auto level-up movesets. Level-up evolution table extracted to
  docs/data/level-evos.json; per-segment reroll plans in docs/data/reroll/seg1..9.
  json. Data in src/data/trainers_frlg.party. Distribution is even (max species ~1%
  of slots, no 3+ intra-team clumps). Known gaps: 127 rematch trainers (_2/_3
  consts) were NOT in scope and still carry vanilla teams; JSON map-order quirks
  (Pokemon Tower high in Segment 5, Nugget Bridge post-gym in Segment 2). Build
  verified (make firered).
- 2026-08-22 - fix - Viridian fisherman flag now also defined in the FRLG flag
  header. FRLG map scripts resolve flags via include/constants/flags_frlg.h, not
  flags.h; FLAG_GOT_VIRIDIAN_SUPER_ROD was only in the latter, causing an
  undefined-reference link error. Repurposed FLAG_0x021 in flags_frlg.h to 0x21 to
  match. (Lesson: FRLG script flags go in flags_frlg.h.)
- 2026-08-22 - trainers/balance - Adopted a per-split trainer LEVEL RAMP rule and
  applied it to Segment 1 (Before Brock, cap 14) as the template. Rule: within
  each gym-gate split, trainer levels rise linearly along the critical path from a
  floor (= the previous split's cap; Segment 1 floor = starter level 5) up to
  cap-1 for the last trainer before the gym, with the gym leader at the cap.
  Segment 1 result (path order): Oak's Lab rival 5 (floor, unchanged); Viridian
  Forest Rick 6, Doug 7, Sammy 9->8, Anthony 7/8->8/9, Charlie 7/7/7->9/9/10;
  Route 22 early rival 9->12 (optional off-path spike, all 3 starter branches);
  Pewter Gym Camper Liam 10/11->12/13 (cap-1); Brock pool 14 (cap, unchanged).
  Data in src/data/trainers_frlg.party. Remaining segments (2-9) still to do;
  docs/data/progression-trainers.json will be regenerated after the full pass.
- 2026-08-22 - items/fishing - Fishing overhaul so rod choice never matters. (1)
  `ChooseWildMonIndex_Fishing` (`src/wild_encounter.c`) now ignores the rod and
  always rolls the super-rod slots (5-9), so Old/Good/Super Rod all pull the same
  fish; wild fishing tables should be authored in slots 5-9 and each water map's
  Surf `water_mons` set to match so fishing and surfing yield the same encounters.
  (2) New Fisherman NPC in Viridian City gives a SUPER ROD early (before the first
  gym) and his dialogue explains rods/Surf are equivalent. Script + text in
  `data/maps/ViridianCity_Frlg/scripts.inc`; object placed in that map's map.json
  (placeholder tile 10,25 by the SW water, reposition in Porymap). Uses a new
  persistent flag `FLAG_GOT_VIRIDIAN_SUPER_ROD` (repurposed 0x21; the FRLG
  `FLAG_GOT_*_ROD` names are all stubbed to 0 in this Emerald-based build and
  cannot be used). Lore fact logged FISH-01 in docs/writing/lore-ledger.md.
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
- 2026-08-22 - pokemon/balance - All species set to the easiest catch rate. Every
  `.catchRate` in `src/data/pokemon/species_info/*.h` (1343 entries) set to 255
  (the max; higher = easier to catch). Legendaries, starters, and everything else
  now catch as easily as a Caterpie. Trade-off: removes catching difficulty as a
  balance lever (Master Ball / status / weakening no longer matter for capture).
- 2026-08-22 - pokemon/gameplay - Caught Pokemon now start at MAXIMUM friendship
  (255). Hooked in `Cmd_givecaughtmon` (`src/battle_script_commands.c`), just
  before `GiveCapturedMonToPlayer`, setting `MON_DATA_FRIENDSHIP` to
  `MAX_FRIENDSHIP`. Only affects wild captures (not gifts, eggs, or starters).
  Makes friendship evolutions immediate and helps Return/Frustration users.
- 2026-08-22 - pokemon/evolutions - Eevee gains stone-based paths for its three
  friendship Eeveelutions so all eight are obtainable without friendship grind:
  Sun Stone → Espeon, Moon Stone → Umbreon, Shiny Stone → Sylveon. The original
  friendship/time/Fairy-move methods are kept alongside. Data in
  `src/data/pokemon/species_info/gen_1_families.h` (inside the existing
  P_GEN_2/P_GEN_6 cross-evo guards).
- 2026-08-22 - items/shops - Celadon Dept. Store 4F clerk now sells the full
  evolution-item set so no trade/item evolution is stuck. Added stones (Ice, Sun,
  Moon, Shiny, Dusk, Dawn, Oval) and trade/held-item evo items (Linking Cord,
  Metal Coat, King's Rock, Dragon Scale, Protector, Electirizer, Magmarizer,
  Up-Grade, Dubious Disc, Reaper Cloth, Prism Scale, Razor Fang, Razor Claw) on
  top of the existing Fire/Thunder/Water/Leaf stones. List in
  `data/maps/CeladonCity_DepartmentStore_4F_Frlg/scripts.inc`. To match the
  evolution-stone price tier (3000), four outlier evo items were flattened to
  `.price = 3000` in `src/data/items.h`: Linking Cord (was 8000), King's Rock
  (was 10000), Razor Fang and Razor Claw (were 15000). Side effect: this is a
  global price change, so their sell value and cost at any other shop also drop.
- 2026-08-22 - pokemon/evolutions - Karrablast and Shelmet can now evolve
  single-player. Both previously had ONLY a partner-species trade evolution
  (Karrablast ↔ Shelmet), which the Linking Cord item does not trigger
  (`src/pokemon.c` item-use path matches EVO_ITEM only). Added an
  `{EVO_ITEM, ITEM_LINKING_CORD, ...}` fallback to each so using a Linking Cord
  evolves Karrablast → Escavalier and Shelmet → Accelgor; the original link-trade
  method is kept. Data in `src/data/pokemon/species_info/gen_5_families.h`.
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
