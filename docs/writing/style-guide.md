# Writing Style Guide

> Scope: **text & flavor only** — never propose sprites, tilesets, portraits, maps, or music.
> Setting: Kanto-authentic FireRed/LeafGreen, gen-1/gen-3 canon only (no later-gen references).

This is the document the creative-director guards and the writer follows. It
defines *how characters talk* and *when to wink vs. play it straight*.

## 1. Core sensibility
- Silly-through-contrast, not blanket goofiness. Humor comes from friction — an
  over-committed character in a low-stakes moment, a straight-man next to a fool.
  A town of earnest gen-1 NPCs is the setup; one absurd character is the punchline.
- Character-first. Every returning character gets a distinct personality. Plot
  beats are fixed; personalities are the canvas.
- Tonal control (the whole job). This is a hard-but-fair hack. If every line is a
  joke, no fight feels dangerous. Know when a character is comic relief and when a
  moment must land straight so a tough battle feels earned.
- Seasoning, not the meal. References/memes/slang are scoped to specific
  characters or optional NPCs. Default NPCs speak in the baseline voice.

## 2. Hard constraints
- Gen-3 text boxes: short two-line pages. Match the width/rhythm of an existing
  nearby vanilla string rather than guessing a character limit.
- Kanto canon only in the writing (matches the Kanto-authentic mechanics).
- Allude, don't reproduce: paraphrase anime characterization; never copy anime
  dialogue verbatim (e.g. the Team Rocket motto) — reword into our own voice.
- Text/flavor only. Reusing an existing vanilla object in Porymap is fine;
  requesting new art is not.

## 3. Character speech styles
("Speech style" = how a character talks — word choice, rhythm, attitude, verbal
tics. No audio; this is all written dialogue.) Assign each character one primary
style. Most NPCs use Baseline.

### Baseline — vanilla Kanto (default)
Light, earnest, a little campy; period-appropriate. This is the sea everything
else contrasts against — keep most NPCs here or the contrast jokes stop working.
Example feel: "The POKéMON here are tougher than they look. Be careful!"

### Gen-Z trainer  [FLAG: dated]
Current slang, lowercase energy, casually over-familiar. Scoped to a handful of
"extremely online" trainers, never townwide. The joke is the clash with Baseline.
Example feel: "ngl your Geodude is kinda mid... it's giving Rock-type."
> Release note: slang dates fast. Tag and review before public release.

### Streamer-homage NPC  [FLAG: release-swap]
Cocky, self-mythologizing, obsessed with "the run" — a nod to Nuzlocke-streamer
culture. Homage, not likeness: evoke a persona via name/team/catchphrase rather
than naming a real person, unless you have their explicit OK.
Example feel: "One death and the whole run's over. I do NOT lose. ...probably."
> Release note: keep optional and off the mandatory path so a release pass can
> genericize or remove them. If naming a real streamer, get permission first.

### Trainer-class voices
- Bug Catcher / Youngster — eager kids, boastful about tiny things.
- Gym Leader — archetypal and self-assured; each also carries their history.
- Team Rocket grunt — menacing-but-comic; petty, never actually competent.
- Hiker / Fisher / etc. — one-note quirks; texture, not stars.

### Anime-flavored characterization  [FLAG: canon-check]
Use anime personalities to deepen characters (Brock the aspiring breeder/cook;
Team Rocket's comic-trio dynamic). Log any anime/game canon contradiction in the
lore ledger.

## 4. Release-readiness flags
Tag inline so a future "make it public" pass is a search, not a rewrite:
- [FLAG: release-swap] — real-person likeness / anything to genericize before release.
- [FLAG: dated] — time-sensitive slang or memes to review periodically.
- [FLAG: canon-check] — anime/game canon blend needing a consistency pass.
Public release is undecided, so apply these from the start — they cost nothing now.

## 5. How this gets used
1. creative-director assigns each character a speech style and decides comic vs.
   straight per moment.
2. writer drafts lines in that style, within gen-3 text-box limits.
3. New lore lines get a row in lore-ledger.md in the same PR.
4. You approve; lines go into the map scripts.pory / text data.
