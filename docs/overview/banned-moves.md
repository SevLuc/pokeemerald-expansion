# Banned moves (player-only)

The player's Pokemon may never carry these moves. **Trainers are unaffected** and
still use them (gyms stay hard). Enforced for player-owned and wild Pokemon only.

Source of truth: `src/data/banned_moves.h` (list + curated replacements).
Engine: `IsMovePlayerBanned` / `GetBannedMoveReplacement` / `ApplyPlayerMoveBans`
in `src/pokemon.c`. Tests: `test/banned_moves.c`.

## The list (76 moves)

### Setup / stat-boost (49)
Swords Dance, Meditate, Sharpen, Howl, Bulk Up, Hone Claws, Nasty Plot, Tail Glow,
Growth, Charge, Iron Defense, Acid Armor, Barrier, Withdraw, Harden, Defense Curl,
Cotton Guard, Dragon Dance, Calm Mind, Cosmic Power, Coil, Quiver Dance, Shell Smash,
Work Up, Agility, Rock Polish, Autotomize, Focus Energy, Belly Drum, Amnesia, Double
Team, Minimize, Curse, Stockpile, Acupressure, Power Trick, Clangorous Soul, Defend
Order, Extreme Evoboost, Fillet Away, Geomancy, No Retreat, Power Shift, Shelter,
Shift Gear, Stuff Cheeks, Take Heart, Tidy Up, Victory Dance

### Protection / stall (8)
Protect, Detect, Endure, King's Shield, Spiky Shield, Baneful Bunker, Wide Guard,
Quick Guard

### Status (2)
Toxic, Will-O-Wisp
(All other status moves stay legal - sleep, paralysis, confusion, etc.)

### Entry hazards (4)
Spikes, Toxic Spikes, Sticky Web, Stealth Rock

### Item / accuracy / other utility (13)
Baton Pass, Destiny Bond, Trick Room, Tailwind, Whirlwind, Roar, Leech Seed, Trick,
Switcheroo, Bestow, Spite, Mind Reader, Lock-On

## Kept legal on purpose
Recovery (Recover / Roost / Wish / Rest / Synthesis / etc.), all non-Toxic/WoW status,
Substitute, Encore, Taunt, Perish Song, Disable, Haze. Skull Bash and Magnet Rise were
reviewed and left legal (Skull Bash attacks; Magnet Rise is utility, not a stat boost).

## What happens when a mon would learn a banned move

The move is removed from the player's copy and, where possible, replaced:

- **Curated same-type egg move (1336 slots).** If the species has an egg move of the
  same type as the banned move, the player's mon learns that instead
  (e.g. Bulbasaur's Growth -> Skull Bash, Leech Seed -> Petal Dance).
- **Backfill (831 slots).** If there's no suitable egg move, the slot is dropped and
  filled from the mon's other legal level-up moves. No blank slots.
- **78 low-confidence** curated picks are non-damaging utility fallbacks (the species
  had no damaging egg move of any type); all on non-Kanto species. Overridable in the
  table.

## Where it's enforced
Capture (wild), gifts / starters / fossils, static encounters, egg hatching, level-up
and evolution move learning, TMs, move tutors, and the Move Relearner. Trainer teams
(auto-generated from the shared level-up learnset) are deliberately left alone.

## Notes / TODO
- "Obtainable" is currently the full National Dex, since all gens are enabled and Kanto
  wild encounters are not yet defined (`wild_encounters.json` is still Emerald data).
  Curated replacements cover the whole dex; revisit if the roster is narrowed.
- Unit tests in `test/banned_moves.c` require the `emerald-test` build target, which
  currently fails on an unrelated pre-existing issue (FRLG-only FLAG_TOGGLE_NO_ENCOUNTERS
  in start_menu.c). The firered ROM itself builds clean with this feature.
