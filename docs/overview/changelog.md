# Changelog

Living record of every gameplay/content change vs. vanilla FireRed. Newest first.
Update in the same PR as the change.

## Format
`YYYY-MM-DD` — area — one-line summary (PR/commit ref)

## Entries
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
