# Elite Four

One section per member: leader, type, level cap, structure, pool, and movesets.
Tracks our hard-but-fair rebalance against vanilla. Cross-link each member's
history to docs/writing/lore-ledger.md.

> STATUS: Lorelei, Bruno, Agatha and Lance pools implemented (trainer entries wired
> in src/data/trainers_frlg.party; Bruno is a 17-mon Fighting+Steel pool, Agatha a
> 14-mon Ghost+Poison pool, Lance a fixed 6-mon all-Dragonite + Zoroark(Illusion)
> pool). Rematch teams (`_2`) and lore fragments are still TODO. Build + playtest on
> Mac.

## Level tiers
The E4 + Champion are draw pools like the gym leaders, keeping the same ace / lead
tags for GENERATION (ace always fielded and sent out last; a `Tags: Lead` mon only
where one must open). LEVELS, however, are the deliberate exception: unlike the gym
leaders, the E4 does NOT snap to the level cap. Every E4 fight shares cap 72, but
the members climb toward the Champion, so their fielded levels are set per-member.

These levels are attached to the fielded SLOT, not to a species: whatever mon the
pool draws into a slot inherits that slot's level (slot 0 = lead, last slot = ace,
per trainer_pools.c). The gym cap-tiering in CreateNPCTrainerPartyFromTrainer still
skips the Elite Four (E4 never snaps to the cap); instead the per-slot spread is
authored in `GetEliteFourPoolSlotLevels` (src/battle_main.c) and applied to any E4
pool trainer that has an entry there:

| Fight | Fielded-6 levels (lead - ace) | Status |
|--|--|--|
| Lorelei | 60 / 61 / 61 / 61 / 61 / 63 | implemented (code) |
| Bruno | 61 / 62 / 63 / 63 / 63 / 65 | implemented (code) |
| Agatha | 63 / 64 / 64 / 65 / 65 / 66 | implemented (code) |
| Lance | 64 / 66 / 66 / 66 / 67 / 69 | implemented (code) |
| Champion | 67 / 68 / 69 / 70 / 70 / 72 | planned |

The `Level:` lines in trainers_frlg.party are fallbacks only for E4 pools with a
slot-level entry; the real fielded levels come from the code table above. Current
data: Lorelei, Bruno, Agatha and Lance are pools driven by the slot-level code;
Champion is 3 variants ~Lv57-63.

## Lorelei (Ice) - first E4 member
- Trainer: `TRAINER_ELITE_FOUR_LORELEI` (rematch `TRAINER_ELITE_FOUR_LORELEI_2`, TODO).
- Level cap: 72 (the `FLAG_IS_CHAMPION` row in src/caps.c; "before / during Elite
  Four" in progression.md). Every moveset below is legal at Lv72 (verified with
  the moveset-legality skill).
- Snow theme: the pool is built around modern Snow (this build sets Snow, not
  Hail: `B_SNOW_WARNING` and `B_PREFERRED_ICE_WEATHER` resolve Snow-setters to the
  Snow weather). Under Snow, Ice-types get +50% Defense, Blizzard is 100%
  accurate, and Snow Cloak / Ice Body come online. Alolan Ninetales sets it for
  free via Snow Warning; several members carry the Snowscape move as backup.

### Structure (draw pool)
- This is a TRAINER POOL of 12 that fields 6, exactly like the gym pools in
  gyms.md (`Party Size: 6`, `Pool Rules: Basic`, `Pool Prune: Bst Match`). The
  game sums the player's team base-stat totals and fields the ace plus the five
  other members whose combined BST is closest to that total
  (`POOL_PRUNE_BST_MATCH` in src/trainer_pools.c). Party Size is fixed at 6 so a
  player cannot shrink Lorelei's team by bringing fewer of their own mons.
- **Ace:** LAPRAS (`Tags: Ace`, always fielded, sent out last).
- **Lead rule (conditional Snow lead):** implemented as a new pick function
  `POOL_PICK_SNOW_LEAD` (src/trainer_pools.c), selected in the party file with
  `Pool Pick Functions: Snow Lead`. For slot 1 it scans the already-fielded mons
  and leads with one whose ability is **Snow Warning** (Alolan Ninetales, free
  turn-1 Snow); if none was drawn it leads with one that knows **Snowscape**
  (Slowbro, Dewgong, Articuno, Froslass, or Glaceon). Alolan Ninetales is NOT
  force-kept, so it stays an ordinary BST-matched candidate; it only leads when
  it is actually fielded.
- **Guarantee (weakened by the Refrigerate Aurorus):** originally, with Party
  Size 6, a snow-setter was always fielded, Lapras reserved as ace, 5 slots drawn
  from 10, only 4 non-setters (Jynx, Mr. Rime, Mamoswine, Weavile), so pigeonhole
  forced at least one setter. Aurorus is a Refrigerate ATTACKER (not a setter), so
  the non-setter count is now 5 (the four above plus Aurorus) out of 11 candidates.
  The 5 drawn slots can in principle all be non-setters, so a snow-setter is NO
  LONGER hard-guaranteed. In practice the six Snowscape / Snow Warning members are
  usually BST-picked, but the pigeonhole no longer holds. To restore the hard
  guarantee, give Aurorus a Snowscape move (making it a setter again) or otherwise
  keep the non-setter count at 4. Re-check whenever the pool composition changes.
- Held items: none. Trainer bag items: Full Restore x2 (AI healing, kept from
  vanilla, same as Misty's Super Potion; not a held item).

### Pool members (12)
Perfect IVs, no EVs, no held items (no items anywhere in this game). Movesets are
legal at Lv72 (the cap). NOTE: fielded levels are now set per SLOT by code, not the
authored Lv72 - Lorelei fields 60/61/61/61/61/63 (see Level tiers). The authored
`Level: 72` lines are legality references / fallbacks only. Snowscape carriers are
marked (snow-setter) since they satisfy the backup-lead rule.

- **ALOLAN NINETALES** (preferred lead), Ice/Fairy, Snow Warning, Timid
  (Blizzard / Moonblast / Icy Wind / Aurora Veil) - sets Snow turn 1; Aurora Veil
  walls the team, Icy Wind chips enemy Speed for the slower members.
- **LAPRAS** (ACE), Water/Ice, Shell Armor, Relaxed
  (Surf / Freeze-Dry / Confuse Ray / Earthquake) - bulky tank; Freeze-Dry beats
  other Waters, Earthquake answers Electric/Steel, Shell Armor blocks crits.
- **SLOWBRO** (snow-setter), Water/Psychic, Regenerator, Sassy
  (Snowscape / Teleport / Psychic / Surf) - pivot; Teleport heals via Regenerator
  and hands momentum to a teammate. The one non-Ice member (canon Lorelei pick).
- **JYNX**, Ice/Psychic, Dry Skin, Timid
  (Ice Beam / Psychic / Aurora Veil / Lovely Kiss) - fast, fragile sweeper with a
  sleep move and screen support off the team's Snow.
- **DEWGONG** (snow-setter), Water/Ice, Ice Body, Timid
  (Blizzard / Drill Run / Snowscape / Surf) - self-sustaining tank; Ice Body heals
  under its own Snow, Drill Run answers Electric/Steel/Fire.
- **ARTICUNO** (snow-setter), Ice/Flying, Snow Cloak, Timid
  (Blizzard / Snowscape / Air Slash / Roost) - self-sufficient snow tank; Snow
  Cloak evasion + Roost recovery under its own Snowscape.
- **FROSLASS** (snow-setter), Ice/Ghost, Snow Cloak, Timid
  (Snowscape / Blizzard / Shadow Ball / Confuse Ray) - fast frail disruptor;
  evasion under Snow plus confusion pressure. Immune to Fighting (patches a
  team-wide Ice weakness).
- **MR. RIME**, Ice/Psychic, Ice Body, Timid
  (Freeze-Dry / Psychic / Icy Wind / Focus Blast) - bulky special attacker; Focus
  Blast covers the Dark/Steel that wall Psychic, Freeze-Dry beats Waters.
- **MAMOSWINE**, Ice/Ground, Thick Fat, Jolly
  (Earthquake / Icicle Crash / Ice Shard / Superpower) - physical breaker and the
  team's answer to Fire/Rock/Steel/Electric; Ice Shard is priority, Thick Fat
  softens its Fire/Ice weaknesses.
- **GLACEON**, Ice, Snow Cloak, Timid
  (Aurora Veil / Blizzard / Freeze-Dry / Snowscape) - slow special nuke and backup
  screen/Snow setter.
- **WEAVILE**, Dark/Ice, Pressure, Jolly
  (Night Slash / Ice Punch / Low Kick / Poison Jab) - fast physical breaker; Ice +
  Dark + Fighting + Poison is near-perfect neutral coverage (Low Kick answers
  Steel, Poison Jab answers Fairy).
- **AURORUS**, Rock/Ice, Refrigerate, Timid
  (Hyper Voice / Discharge / Earth Power / Hyper Beam) - offensive Refrigerate
  build: Refrigerate turns Hyper Voice and Hyper Beam into boosted Ice STAB, with
  Discharge (Electric) + Earth Power (Ground) giving near-complete coverage
  (Ice/Electric/Ground). Not a snow-setter (see the weakened guarantee above);
  cannot learn Power Gem in this build, and it carries no Rock STAB here.

### Notes / gaps
- Dropped during pool-building: Cloyster and Iron Bundle (Iron Bundle's strong
  Water STAB Hydro Pump is cap-locked at L72, leaving it a weak mono-Ice attacker).
- Team-wide shared weaknesses (Ice-heavy roster): Fire, Rock, Steel, Fighting.
  Mamoswine (Ground/Rock/Fighting coverage) and Weavile (Low Kick) are the
  deliberate answers; Froslass is immune to Fighting.

### Done
- [x] Party Size 6, BST-matched draw pool of 11 (like the gyms).
- [x] Conditional Snow-lead rule (`POOL_PICK_SNOW_LEAD` in src/trainer_pools.c):
      Ninetales first if fielded, else a Snowscape carrier. Covered by a test in
      test/battle/trainer_control.c ("Trainer Party Pool Snow Lead ...").
- [x] Lorelei's trainer entry wired in src/data/trainers_frlg.party.

### TODO
- [ ] Build + playtest on Mac (this was authored in a web session, not compiled).
- [ ] Rematch team (`_2`).
- History fragments: see LORELEI-* in docs/writing/lore-ledger.md (TODO).

## Bruno (Fighting + Steel) - second E4 member
- Trainer: `TRAINER_ELITE_FOUR_BRUNO` (rematch `TRAINER_ELITE_FOUR_BRUNO_2`, TODO).
- Level cap: 72 (shared E4 cap). Bruno does NOT snap to the cap; his fielded 6
  climb toward the Champion at 61 / 62 / 63 / 63 / 63 / 65 (lead - ace), set per
  slot by `GetEliteFourPoolSlotLevels` (see Level tiers above).
- Theme: reflavoured from a pure Fighting master into a "fists of steel" martial
  discipline - Fighting types plus a Steel core (plus one Ground pick, Sandslash).
  Every moveset verified legal in this build with the moveset-legality skill.

### Structure (draw pool)
- A TRAINER POOL of 17 that fields 6, like the gyms and Lorelei (`Party Size: 6`,
  `Pool Rules: Basic`, `Pool Prune: Bst Match`). The game fields the ace plus the
  five members whose combined BST is closest to the player's team BST total.
- **Ace:** NamasteNiffo (MACHAMP) (`Tags: Ace`, always fielded, sent out last).
- No forced lead: whichever mon is drawn into slot 0 leads (and takes the lead
  level, 61). No held items anywhere. Trainer bag items: Full Restore x2 (kept
  from vanilla, AI healing, same as Lorelei).

### Pool members (17)
Nicknames in quotes. Ability / nature / moves. All legal at their fielded level.

Fighting (9):
- **"NamasteNiffo" MACHAMP** (ACE), No Guard, Jolly
  (Dynamic Punch / Stone Edge / Payback / Fire Blast) - No Guard makes Dynamic
  Punch, Stone Edge AND Fire Blast never miss.
- **"360 NOSCOPE" HITMONLEE**, Reckless, Jolly
  (High Jump Kick / Sucker Punch / Earthquake / Mach Punch) - Reckless-boosted HJK
  nuke plus double priority.
- **HITMONCHAN**, Iron Fist, Jolly
  (Close Combat / Bullet Punch / Ice Punch / Fire Punch) - Iron Fist boosts the
  three punches; the elemental-fist boxer.
- **URSHIFU (Single Strike)**, Unseen Fist, Jolly
  (Wicked Blow / Close Combat / Sucker Punch / Ice Punch) - always-crit Dark STAB
  that ignores Protect.
- **URSHIFU (Rapid Strike)**, Unseen Fist, Jolly
  (Surging Strikes / Close Combat / Aqua Jet / Poison Jab) - three guaranteed
  crits, ignores Protect.
- **POLIWRATH**, Water Absorb, Jolly
  (Close Combat / Liquidation / Ice Punch / Earthquake) - heals off any Water move.
- **LUCARIO**, Inner Focus, Timid
  (Aura Sphere / Flash Cannon / Dark Pulse / Vacuum Wave) - special breaker with
  special-priority Vacuum Wave. The Fighting/Steel bridge.
- **HAWLUCHA**, Mold Breaker, Jolly
  (Close Combat / Acrobatics / Rock Tomb / Dig) - fast coverage attacker; Mold
  Breaker Dig hits Levitate mons.
- **HERACROSS**, Moxie, Jolly
  (Close Combat / Megahorn / Earthquake / Rock Tomb) - Moxie snowball.

Steel (7):
- **"banksy" GHOLDENGO**, Good as Gold, Timid
  (Flash Cannon / Shadow Ball / Power Gem / Focus Blast) - immune to all status
  moves; immune to Fighting (patches the team's shared Fighting weakness).
- **MAGNEZONE**, Analytic, Modest
  (Thunderbolt / Flash Cannon / Magnet Rise / Body Press) - Magnet Rise covers its
  4x Ground weakness.
- **EMPOLEON**, Torrent, Timid
  (Surf / Flash Cannon / Ice Beam / Roost) - fast special pivot with recovery.
- **BRONZONG**, Levitate, Brave
  (Iron Head / Earthquake / Confuse Ray / Zen Headbutt) - Levitate = Ground immune.
- **FERROTHORN**, Iron Barbs, Relaxed
  (Power Whip / Iron Head / Bulldoze / Body Press) - Body Press off 131 Def; Iron
  Barbs contact chip.
- **TOGEDEMARU**, Iron Barbs, Jolly
  (Iron Head / Zing Zap / Nuzzle / Magnet Rise) - flinch/paralysis pressure.
- **STEELIX**, Sheer Force, Adamant
  (Iron Head / Rock Slide / Crunch / Thunder Fang) - all four moves get the Sheer
  Force boost; no Ground STAB by design.

Ground (1):
- **SANDSLASH**, Sand Veil, Adamant
  (Earthquake / Rock Slide / Leech Life / Sand Attack) - disruptive/sustain; the
  one off-theme pick.

### Notes / gaps
- Team-wide shared weaknesses lean on the Steel core; Gholdengo (Fighting-immune)
  and the Steel bulk cover the Fighting-weak members. Sandslash is off-theme (pure
  Ground) by deliberate choice.

### Done
- [x] Party Size 6, BST-matched draw pool of 17 (like the gyms / Lorelei).
- [x] Per-slot fielded levels via `GetEliteFourPoolSlotLevels` (src/battle_main.c);
      Bruno 61/62/63/63/63/65, and Lorelei brought onto her planned 60/61/61/61/61/63.
- [x] Bruno's trainer entry wired in src/data/trainers_frlg.party (validated with
      the trainerproc tool: all 17 species / abilities / moves resolve).

### TODO
- [ ] Build + playtest on Mac (authored in a web session, not compiled/ROM-tested).
- [ ] Rematch team (`_2`).
- History fragments: see BRUNO-* in docs/writing/lore-ledger.md (TODO).

## Agatha (Ghost + Poison) - third E4 member
- Trainer: `TRAINER_ELITE_FOUR_AGATHA` (rematch `TRAINER_ELITE_FOUR_AGATHA_2`, TODO).
- Level cap: 72 (shared E4 cap). Agatha does NOT snap to the cap; her fielded 6
  climb 63 / 64 / 64 / 65 / 65 / 66 (lead - ace), set per slot by
  `GetEliteFourPoolSlotLevels` (see Level tiers above).
- Theme: canon gen-1 Agatha (Gengar / Golbat / Haunter / Arbok) reframed as a
  Ghost + Poison pool. A disruption-heavy roster (Confuse Ray / Will-O-Wisp /
  Spore / Strength Sap) around hard-hitting Ghosts. Every moveset legality-checked.
- NOTE: Gengar's only ability here is Cursed Body (this build sets
  `P_UPDATED_ABILITIES = GEN_LATEST`), NOT Levitate - so Gengar keeps the standard
  Ghost/Poison weaknesses (Ground, Psychic, Ghost, Dark).

### Structure (draw pool)
- A TRAINER POOL of 14 that fields 6, like the gyms and the other E4
  (`Party Size: 6`, `Pool Rules: Basic`, `Pool Prune: Bst Match`).
- **Ace:** GENGAR (`Tags: Ace`, always fielded, sent out last).
- No forced lead: whichever mon is drawn into slot 0 leads (takes the lead level,
  63). No held items. Trainer bag: Full Restore x2 (AI healing, like Lorelei/Bruno).

### Pool members (14)
Ability / nature / moves. All legal at their fielded level.

Ghost (10):
- **GENGAR** (ACE), Ghost/Poison, Cursed Body, Timid
  (Sludge Wave / Shadow Ball / Dazzling Gleam / Confuse Ray)
- **POLTEAGEIST**, Ghost, Cursed Body, Timid
  (Will-O-Wisp / Strength Sap / Shadow Ball / Confuse Ray) - defensive annoyer.
- **MISMAGIUS**, Ghost, Levitate, Timid
  (Confuse Ray / Shadow Ball / Mystical Fire / Dazzling Gleam)
- **DUSKNOIR**, Ghost, Pressure, Adamant
  (Poltergeist / Shadow Sneak / Thunder Punch / Revenge) - bulky physical.
- **DRAGAPULT**, Dragon/Ghost, Clear Body, Jolly
  (Dragon Darts / U-turn / Phantom Force / Infestation) - fast pivot/chipper.
- **MIMIKYU**, Ghost/Fairy, Disguise, Jolly
  (Play Rough / Shadow Claw / Confuse Ray / Will-O-Wisp) - Disguise buys a free
  status turn.
- **CHANDELURE**, Ghost/Fire, Flame Body, Timid
  (Flamethrower / Shadow Ball / Energy Ball / Confuse Ray) - 145 SpA nuke.
- **DRIFBLIM**, Ghost/Flying, Aftermath, Calm
  (Shadow Ball / Air Slash / Strength Sap / Thunder Wave) - 150-HP staller.
- **BASCULEGION**, Water/Ghost, Adaptability, Jolly
  (Wave Crash / Last Respects / Aqua Jet / Head Smash) - Last Respects scales with
  fainted allies; 2x STAB via Adaptability.
- **DHELMISE**, Ghost/Grass, Steelworker, Brave
  (Anchor Shot / Grassy Glide / Earthquake / Synthesis) - trapping tank (Power Whip
  is cap-locked at L64, so no Ghost STAB).

Poison (4):
- **CROBAT**, Poison/Flying, Infiltrator, Jolly
  (Brave Bird / Cross Poison / U-turn / Roost) - fast pivot.
- **AMOONGUSS**, Grass/Poison, Regenerator, Relaxed
  (Energy Ball / Sludge Bomb / Foul Play / Spore) - fat Spore/Regenerator pivot.
- **DRAGALGE**, Poison/Dragon, Adaptability, Modest
  (Draco Meteor / Sludge Wave / Hydro Pump / Flip Turn) - 2x-STAB special breaker.
- **SNEASLER**, Fighting/Poison, Poison Touch, Jolly
  (Close Combat / Dire Claw / Fake Out / U-turn) - Hisuian line, no Ice moves.

### Notes / gaps
- Disruption-heavy but every status is "fair" (Confuse Ray, Will-O-Wisp, para) with
  the one exception of Amoonguss's Spore (100% sleep) - flag if that crosses the line.
- Reuse: none of Agatha's mons overlap the other implemented pools.

### Done
- [x] Party Size 6, BST-matched draw pool of 14.
- [x] Agatha slot spread {63,64,64,65,65,66} added to `GetEliteFourPoolSlotLevels`.
- [x] Agatha's trainer entry wired in src/data/trainers_frlg.party (validated with
      the trainerproc tool: all 14 species / abilities / moves resolve).

### TODO
- [ ] Build + playtest on Mac (authored in a web session, not compiled/ROM-tested).
- [ ] Rematch team (`_2`).
- History fragments: see AGATHA-* in docs/writing/lore-ledger.md (TODO).

## Lance (Dragon) - fourth E4 member
- Trainer: `TRAINER_ELITE_FOUR_LANCE` (rematch `TRAINER_ELITE_FOUR_LANCE_2`, TODO).
- Level cap: 72. Fielded levels 64 / 66 / 66 / 66 / 67 / 69 (from
  `GetEliteFourPoolSlotLevels`, src/battle_main.c). Every moveset is legal at cap 72,
  verified with the moveset-legality skill (one deliberate exception below).
- Concept: Lance fields SIX Dragonites, and one of them is secretly a Zoroark using
  Illusion to appear as a sixth Dragonite. It is the classic "count the Dragonites"
  trap. The player who auto-pilots Ice Beam into the team (Dragonite is 4x weak) eats
  a surprise, Ice is only neutral on the Dark-type Zoroark, and once it is revealed
  they face a fast special attacker mid-momentum.

### Structure (fixed pool, all 6 fielded)
- `Party Size: 6`, `Pool Rules: Basic`, `Pool Prune: None`. Pool size = party size =
  6, so there is NO BST draw or substitution; Lance always fields exactly these six.
- **Ace:** one Dragonite (`Tags: Ace`). Aces are always fielded and pinned to the
  LAST party slot (sent out last, slot level 69), per trainer_pools.c.
- **Randomised order:** the pool runs `RandomizePoolIndices` (Fisher-Yates) every
  battle, so the five non-ace mons are shuffled across slots 0-4. Because slot levels
  are attached to the SLOT (64/66/66/66/67), not the species, the Zoroark lands on a
  random slot with a level identical to whatever Dragonite would have sat there. Its
  position AND its level are therefore un-fingerprintable.
- **Why the disguise always holds:** the Illusion picker (`GetIllusionMonPartyId`,
  src/battle_util.c) copies the LAST living party member. The Ace Dragonite occupies
  the final array slot and is sent out last, so it is alive behind the Zoroark
  whenever the Zoroark enters. Zoroark therefore always copies a Dragonite, and is
  never itself the last-alive mon (which would drop Illusion). Since the Dragonites
  are un-nicknamed, the disguise reads "DRAGONITE" on the health bar and in every
  battle message until the Zoroark takes a damaging hit.
- Held items: none. Trainer bag items: Full Restore x2 (AI healing, kept from vanilla).

### Pool members (6)
Perfect IVs (31), no EVs, no held items. All five Dragonites run **Multiscale** (they
survive one Ice/Fairy hit from full HP; three carry Roost to re-arm it). The one real
team weakness left open, on purpose, is a dedicated Fairy attacker; the fair counter
to a mono-Dragon gimmick.

| Slot role | Species | Ability | Nature | Moves |
|--|--|--|--|--|
| **Ace** (Lv69) | Dragonite | Multiscale | Jolly | Outrage / Extreme Speed / Earthquake / Iron Head |
| Disruptor | Dragonite | Multiscale | Jolly | Thunder Wave / Supersonic / Dragon Claw / Fire Punch |
| Annoyer | Dragonite | Multiscale | Jolly | Breaking Swipe / Roost / Mud-Slap / Dual Wingbeat |
| Special coverage | Dragonite | Multiscale | Timid | Dragon Pulse / Air Slash / Flamethrower / Surf |
| Special nuke | Dragonite | Multiscale | Timid | Draco Meteor / Fire Blast / Hurricane / Focus Blast |
| **Impostor** | Zoroark | Illusion | Timid | Night Daze / Aura Sphere / Flamethrower / Sludge Bomb |

- **Ace** answers Fairies itself with Iron Head (2x); Extreme Speed gives priority.
- **Impostor** is built to punish the Ice-Beam trap and to specialise in killing
  Ice / Steel / Fairy / Rock: Aura Sphere covers Ice/Steel/Rock, Sludge Bomb covers
  Fairy, Flamethrower is the reliable Ice/Steel backup, Night Daze is the STAB.

### Notes / gaps
- **Aura Sphere is a deliberate learnset addition.** Zoroark cannot normally learn it
  in this build; `MOVE_AURA_SPHERE` was added to its entry in
  src/data/pokemon/all_learnables.json (and the docs mirror docs/data/movepools.json)
  so the moveset-legality skill accepts it. Because Aura Sphere is not a TM/tutor/
  universal move, the generated player-facing teachable list does NOT pick it up, so
  this stays a Lance-only move; the player's Zoroark still has no way to learn it.
- Fairy-type attackers remain the intended, fair answer to the whole team.

### Done
- [x] Party Size 6, fixed pool of 6 (Pool Prune: None), all fielded.
- [x] Lance slot spread {64,66,66,66,67,69} added to `GetEliteFourPoolSlotLevels`.
- [x] Lance's trainer entry wired in src/data/trainers_frlg.party (Ace tag on the
      Dragonite; five non-ace mons shuffled by the pool each battle).
- [x] Aura Sphere added to Zoroark's learnable pool (Lance-only, no player leak).

### TODO
- [ ] Build + playtest on Mac (authored in a web session, not compiled/ROM-tested).
- [ ] Rematch team (`_2`).
- History fragments: see LANCE-* in docs/writing/lore-ledger.md (TODO).
