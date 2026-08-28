# Custom battle music (drop-in)

This project can add extra battle themes (for example Gen 4, HGSS, or SwSh
arrangements) alongside the stock FRLG and Emerald tracks, without
committing any copyrighted audio to the repo. When enabled, each battle
randomly picks from a pool of all available tracks for that category -
FRLG, Emerald, and custom drop-ins all weighted equally - keeping the
music fresh across generations. The wiring is committed; the actual music
files stay on your machine and are git-ignored, the same way the base ROM
is never committed.

## What is and is not committed

- Committed (safe, not audio): the config flag, the song-table slots, the
  `MUS_CUSTOM_VS_*` constants, the `midi.cfg` lines, and the battle-music
  remap in `GetBattleBGM`.
- NOT committed (yours, supplied locally): the `.mid` files themselves. They
  are listed in `.gitignore` (`sound/songs/midi/mus_custom_vs_*.mid`) so they
  can never be pushed. Do not force-add them. Only commit music you have the
  right to distribute.

## The slots

| Slot file (drop into `sound/songs/midi/`) | Pool |
| --- | --- |
| `mus_custom_vs_wild.mid`     | Wild: FRLG + Emerald + this (1-in-3) |
| `mus_custom_vs_trainer.mid`  | Trainer: FRLG + Emerald + this (1-in-3) |
| `mus_custom_vs_gym.mid`      | Gym Leader: FRLG + Emerald + this + SwSh (1-in-4) |
| `mus_custom_vs_gym_swsh.mid` | Gym Leader: SwSh arrangement (1-in-4) |
| `mus_custom_vs_rival.mid`    | Rival: vanilla + this (1-in-2) |
| `mus_custom_vs_champion.mid` | Champion: FRLG + Emerald + this + HGSS + ORAS (1-in-5) |
| `mus_custom_vs_champion_hgss.mid` | Champion: HGSS arrangement (1-in-5) |
| `mus_custom_vs_champion_oras.mid` | Champion: ORAS/RSE arrangement (1-in-5) |
| `mus_custom_vs_legend.mid`   | Legendary: FRLG + this (1-in-2) |
| `mus_custom_vs_evil_leader.mid` | Evil team leader: Emerald + this (1-in-2) |
| `mus_custom_vs_elite_four.mid` | Elite Four: Emerald + RSE + BW (1-in-3) |
| `mus_custom_vs_elite_four_bw.mid` | Elite Four: BW arrangement (1-in-3) |

You do not need all slots. Any slot whose file you leave out simply is not built;
just make sure `USE_CUSTOM_BATTLE_MUSIC` is only ON once the files you DO want
are present (a missing file for an enabled slot fails the build at link time).

## Steps

1. Get each track as a **GBA-format `.mid`**. Gen 4 games are DS titles whose
   music is in a DS sound format the GBA engine here cannot play, so a track
   has to be re-sequenced into a GBA MIDI (and ideally given a GBA voicegroup).
   This is arrangement work, not a file copy.
2. Name the files exactly as in the table above and drop them into
   `sound/songs/midi/`.
3. (Optional) For authentic instruments, add a voicegroup and point the track's
   `-G` option at it in `sound/songs/midi/midi.cfg`. Out of the box those lines
   reuse the existing FRLG battle instrument banks, so a dropped-in track is
   immediately playable, just with FRLG instruments.
4. Set `USE_CUSTOM_BATTLE_MUSIC` to `TRUE` in `include/config/general.h`.
5. `make firered` and test. Each battle category above now plays your track.

To go back to stock themes only, set `USE_CUSTOM_BATTLE_MUSIC` back to
`FALSE` (the files can stay where they are; they are simply not referenced).
When the flag is `TRUE`, FRLG, Emerald, and custom tracks all play in
rotation regardless of current region - no option menu toggle, the game
picks randomly each battle.

## Looping

Downloaded/ripped MIDIs usually have no loop markers, so by default mid2agb builds
them to play once and stop. Every `mus_custom_vs_*` line in `midi.cfg` carries the
`-LOOP` flag, which makes mid2agb loop the whole track back to the start when the
MIDI has no explicit `[` / `]` loop points. If your MIDI DOES contain its own loop
markers, those win and `-LOOP` does nothing. To add a custom track that should loop,
just keep the `-LOOP` on its `midi.cfg` line (it is there already for all stock
slots). Songs are unaffected in every other build.

## Notes

- DS-era tracks often use more instruments than the GBA's channel budget
  allows, so straight conversions can sound thin or exceed the sample budget.
  Expect some per-track trimming.
- This is independent of the MUSIC SPEED option; a custom battle track is
  sped up by the same tempo setting as any other BGM.
