# Changelog

Living record of every gameplay/content change vs. vanilla FireRed. Newest first.
Update in the same PR as the change.

## Format
`YYYY-MM-DD` — area — one-line summary (PR/commit ref)

## Entries
- 2026-08-19 — QoL — Auto-heal after battle. New config flag `OW_HEAL_AFTER_BATTLE`
  (include/config/overworld.h, default TRUE) fully restores the party (HP, status,
  PP) after every won/ended wild, trainer, rematch, and scripted/legendary encounter,
  removing Pokémon Center trips. Excludes battle facilities (Frontier, Trainer
  Tower/Hill), link, Safari, recorded, and tutorial battles. Trade-off: removes
  battle-to-battle attrition as a difficulty lever. Verify in-game: after a normal
  wild/trainer fight the party is full HP/status/PP; inside Trainer Tower it is not.
- 2026-08-17 — setup — Project scaffolded from rh-hideout/pokeemerald-expansion
  (fork SevLuc/pokeemerald-expansion), FireRed target, CLAUDE.md + docs/ created.
  No gameplay changes yet; all config at expansion defaults.
