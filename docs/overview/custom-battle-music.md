# Custom battle music (drop-in)

This project can swap the battle themes for your own tracks (for example
Gen 4 arrangements) without committing any copyrighted audio to the repo. The
wiring is committed; the actual music files stay on your machine and are
git-ignored, the same way the base ROM is never committed.

## What is and is not committed

- Committed (safe, not audio): the config flag, the song-table slots, the
  `MUS_CUSTOM_VS_*` constants, the `midi.cfg` lines, and the battle-music
  remap in `GetBattleBGM`.
- NOT committed (yours, supplied locally): the `.mid` files themselves. They
  are listed in `.gitignore` (`sound/songs/midi/mus_custom_vs_*.mid`) so they
  can never be pushed. Do not force-add them. Only commit music you have the
  right to distribute.

## The six slots

| Slot file (drop into `sound/songs/midi/`) | Used for |
| --- | --- |
| `mus_custom_vs_wild.mid`     | Wild battles |
| `mus_custom_vs_trainer.mid`  | Regular trainer battles |
| `mus_custom_vs_gym.mid`      | Gym Leader battles |
| `mus_custom_vs_rival.mid`    | Rival battles |
| `mus_custom_vs_champion.mid` | Champion battles |
| `mus_custom_vs_legend.mid`   | Legendary battles |

You do not need all six. Any slot whose file you leave out simply is not built;
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

To go back to the stock themes, set `USE_CUSTOM_BATTLE_MUSIC` back to `FALSE`
(the files can stay where they are; they are simply not referenced).

## Notes

- DS-era tracks often use more instruments than the GBA's channel budget
  allows, so straight conversions can sound thin or exceed the sample budget.
  Expect some per-track trimming.
- This is independent of the MUSIC SPEED option; a custom battle track is
  sped up by the same tempo setting as any other BGM.
