# Elite Four

One section per member: leader, type, level cap, structure, pool, and movesets.
Tracks our hard-but-fair rebalance against vanilla. Cross-link each member's
history to docs/writing/lore-ledger.md.

> STATUS: Lorelei pool drafted (movesets + abilities + natures). Party size and
> the fought subset are not yet decided; pool mechanics need implementation in
> src/trainer_pools.c. See TODOs below.

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
- This is a TRAINER POOL that Lorelei draws her fought team from (like the gym
  pools in gyms.md). Party size and the prune rule are TODO (E4 standard is 5-6;
  decide before implementing).
- **Ace:** LAPRAS (always fielded).
- **Lead rule (conditional Snow lead):** ALOLAN NINETALES is the preferred lead
  and is sent out first whenever it is in the fielded team, so it sets Snow on
  turn 1 with Snow Warning. **If Alolan Ninetales is NOT fielded, a Pokemon that
  knows Snowscape must lead instead** (Slowbro, Dewgong, Articuno, Froslass, or
  Glaceon), so Snow is up on turn 1 regardless of who is drawn. NEEDS
  IMPLEMENTATION in src/trainer_pools.c (a conditional-lead rule; the existing
  `POOL_TAG_LEAD` is an unconditional forced lead, so this needs a small
  extension or a Snowscape-carrier fallback).

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

### TODO
- [ ] Decide party size and the fielded subset (or keep all 11 as a BST-matched
      draw pool like the gyms).
- [ ] Implement the conditional Snow-lead rule (Ninetales first if fielded, else a
      Snowscape carrier) in src/trainer_pools.c, plus a test in
      test/battle/trainer_control.c.
- [ ] Write Lorelei's trainer entry (Showdown syntax) once the fielded set is
      fixed; wire the pool.
- [ ] Rematch team (`_2`).
- History fragments: see LORELEI-* in docs/writing/lore-ledger.md (TODO).
