# Elite Four

One section per member: leader, type, level cap, structure, pool, and movesets.
Tracks our hard-but-fair rebalance against vanilla. Cross-link each member's
history to docs/writing/lore-ledger.md.

> STATUS: Lorelei pool implemented (trainer entry wired in
> src/data/trainers_frlg.party with the new Snow Lead pick function). Rematch
> team (`_2`) and lore fragments are still TODO. Build + playtest on Mac.

## Planned level tiers (NOT yet applied)
The E4 + Champion will be rebuilt as draw pools like the gym leaders (ace at cap,
cap-2 bulk, cap-4 lead only where a `Tags: Lead` mon exists). When those teams are
built, tier the fielded 6 to these target spreads. Levels not applied to the
current trainer data yet - noted here for the rebuild:

| Fight | Fielded-6 levels (lead - ace) |
|--|--|
| Lorelei | 60 / 61 / 61 / 61 / 61 / 63 |
| Bruno | 61 / 62 / 63 / 63 / 63 / 65 |
| Agatha | 63 / 64 / 64 / 65 / 65 / 66 |
| Lance | 64 / 66 / 66 / 66 / 67 / 69 |
| Champion | 67 / 68 / 69 / 70 / 70 / 72 |

Current data (unchanged): Lorelei pool all Lv72; Bruno/Agatha/Lance vanilla 5-mon
teams; Champion 3 variants ~Lv57-63.

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
