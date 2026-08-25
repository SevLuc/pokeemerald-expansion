# Elite Four

One section per member: leader, type, level cap, structure, pool, and movesets.
Tracks our hard-but-fair rebalance against vanilla. Cross-link each member's
history to docs/writing/lore-ledger.md.

> STATUS: Lorelei and Bruno pools implemented (trainer entries wired in
> src/data/trainers_frlg.party; Bruno is a 17-mon Fighting+Steel draw pool).
> Rematch teams (`_2`) and lore fragments are still TODO. Build + playtest on Mac.

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
| Agatha | 63 / 64 / 64 / 65 / 65 / 66 | planned |
| Lance | 64 / 66 / 66 / 66 / 67 / 69 | planned |
| Champion | 67 / 68 / 69 / 70 / 70 / 72 | planned |

The `Level:` lines in trainers_frlg.party are fallbacks only for E4 pools with a
slot-level entry; the real fielded levels come from the code table above. Current
data: Lorelei and Bruno are pools driven by the slot-level code; Agatha/Lance are
still vanilla 5-mon teams; Champion is 3 variants ~Lv57-63.

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
- This is a TRAINER POOL of 11 that fields 6, exactly like the gym pools in
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
- **Guarantee:** with Party Size 6, a snow-setter is always fielded. Lapras is
  the ace, leaving 5 slots drawn from 10 candidates, and only 4 of those are
  non-setters (Jynx, Mr. Rime, Mamoswine, Weavile). By pigeonhole at least one of
  the 5 is a snow-setter, so the lead rule never has an empty hand. This holds as
  long as (Party Size - reserved) stays greater than the count of non-setters; if
  the pool composition changes, re-check it.
- Held items: none. Trainer bag items: Full Restore x2 (AI healing, kept from
  vanilla, same as Misty's Super Potion; not a held item).

### Pool members (11)
All at Lv72 = at the cap, perfect IVs, no EVs, no held items (no items anywhere in
this game). Snowscape carriers are marked (snow-setter) since they satisfy the
backup-lead rule.

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
