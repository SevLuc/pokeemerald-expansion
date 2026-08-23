# Locke - rival voice (CHARACTER CORE)

> Rival: **Locke** (a selectable rival identity at the new-game intro, stored in
> VAR_RIVAL_ID, alongside Buhrito the default and Twitch).
> Voice: the style-guide **Streamer-homage NPC** [FLAG: release-swap]: cocky,
> self-mythologizing, obsessed with "the run," nuzlocke-streamer culture. HOMAGE,
> NOT likeness: evoke the persona through name/team/catchphrase; never name or
> unmistakably caricature a real streamer.
>
> Status: character-core design doc. The sample battle lines below are DRAFTS to
> set the voice, NOT final in-game text. Wiring (VAR_RIVAL_ID branches, gen-3 line
> breaks \n \p \l) happens later, same as buhrito.md / twitch.md.
>
> Scaffold + vanilla baseline to fork from: drafts/rival-encounters.md
> Sibling voice docs (structure to match): drafts/buhrito.md, drafts/twitch.md
> Ledger rows: ../lore-ledger.md (LOCKE-*).
> RULES that still apply to every line: no em dashes; short gen-3 pages.

---

## One line

The warmest man behind a camera: Locke narrates his whole run to a chat he loves,
genuinely adores Pokemon, roots for everyone (his rival included), thanks people
just for playing, and pours out so much sincere encouragement that you barely
notice the faint ache underneath, the quiet not-knowing whether anyone's watching.

## The concept: The Documentarian

Locke is always RECORDING THE RUN. Every battle is an "episode" for a stream / an
audience he treats as beloved guests. He narrates his own fights (including his
defeats) as content, talking to a chat he adores and thanking them for being there.
The core of him is WARMTH: he loves this game, he wants everyone to love it too, he
celebrates the player even as their rival, and he thanks people, sincerely, just
for showing up.

**The engine (silly-through-contrast):** a relentlessly SUPPORTIVE, grateful,
game-loving showman vs. a faint ache he never names. The dominant read is wholesome:
he hypes your team, congratulates your wins over him, urges the audience to go start
their own run, means every "thank you." The comedy is the sheer volume of sincere
encouragement poured at a room he can't see answer back. Two things hold it up:
- His warmth is REAL, not a bit. The gratitude and encouragement are load-bearing;
  the sincerity is the straight man to his carnival-barker delivery. He also
  genuinely REVERES "the run" as a sacred vow (permadeath, deathless, one life).
- The unseen audience is the faint undertone. He loves them so openly that the
  silence answering back becomes the only shadow on him, and it stays a shadow.

Keep it MOSTLY WARM. The pathos is a faint undertone, not the thesis: it is just
the small cost of aiming this much sincere love at an audience he can't confirm is
there. It peeks through in glimpses, never mawkish, never a speech. Even the sad
beats are mostly carried by his love of the game, not by hollowness.

## Locked voice + release flag

- **Streamer-homage NPC** [FLAG: release-swap]. Warm, encouraging, game-loving
  showman; "the run" is scripture but the audience is beloved. Style-guide example
  feel: "One death and the whole run's over. I do NOT lose. ...but hey, you might.
  Go find out. Seriously, go play."
- Verbal kit: "we're LIVE," "chat," "clip that," "great content," "the run,"
  "deathless," "the vow," "roll it," "that's a wrap," a gracious-host spin on every
  loss ("beautiful," "struggle sells," "the people love an underdog arc"). He talks
  TO the camera and ABOUT himself in showrunner terms (episode, season finale, arc).
- **Supportive / grateful / encouraging kit (the core):** "thank you for playing,"
  "thanks for being here," "so glad you're here," "you're doing GREAT," "look at
  that team, that's beautiful," "go start your own run," "that's a future champ
  right there," and celebrating the PLAYER'S win over him without a sulk ("that was
  a clean beat, chat, give it up for the challenger"). "Thank you for playing" /
  "thanks for being here" is his SIGNATURE note; land it often. He is a supportive
  rival, never a sore loser; every viewer is a future trainer he's rooting for.
- Sign-off slot (vanilla ends beats on "Smell ya later!"): Locke signs off like a
  broadcast wrapping. Candidate: "...And we're clear." / "That's the episode."
- HARD LINE ON HOMAGE: the persona is a composite of nuzlocke-streamer CULTURE, not
  one person. Do not lift a real creator's catchphrase, handle, or signature bit.
  (Buhrito and Twitch already carry the named-scene references; Locke stays the
  generic archetype so a release pass can keep or cut him cleanly.)

## How his mechanics read as lore

Locke's implemented mechanics ARE his character. Do not contradict them; lean on
them.
- **He plays a nuzlocke every save.** This is why he is "Father of the Nuzlocke" at
  the pick, and why the run is sacred to him. The vow is real to him even though,
  in our mechanics, his mons never actually die.
- **The kept counter-starter, held back as his ace, never led.** Read as lore: the
  showman always keeps his best card off-camera for the finale. His ace is the one
  mon that is the SAME every run, the through-line of the series, so he saves it.
- **His lead is always his least-weak mon; the rest are generated fresh each save**
  from the wild tables of the areas he has reached (one per area, no duplicate
  species, evolved to level, chosen for coverage). Read as lore: "no two runs play
  out the same" is LITERALLY true, which is exactly the pitch a documentarian makes.
  Every season is a new cast; only the ace recurs.
- **The team grows cumulatively across the game.** Read as lore: the series has a
  running roster that fills out episode by episode.

Tonal control: none of this softens the FIGHT. His ace hard-counters your starter
and comes out late; the generated team is built for coverage. The comedy is the
narration wrapped around a fight that is genuinely dangerous. He performs before
and after; inside the battle he is deadly.

## Battle voice (SAMPLE DRAFTS, not final)

> Marked samples to LOCK THE VOICE, one intro + one loss-spin per beat. Final
> per-beat lines get written and wired later (like buhrito.md). No em dashes;
> gen-3 short pages added at wiring. The intro can be showman; the LOSS is spun as
> content AFTER the fight, so the fight itself still lands.

- **Oak's Lab (Ep. 1):**
  - intro: `And we're LIVE. Day one, fresh save. Say hi to the new challenger, chat. ...Oh, you're gonna be GOOD.`
  - loss spin: `Ohh, we take the L on episode one! And chat, what a beat. Give it up for the challenger. Thank you for playing, seriously. This is why I love this game.`
- **Route 22 (early):**
  - intro: `Still rolling, chat. Look who followed us out of the lab. Camera's on you, superstar. Show 'em what you've got.`
  - loss spin: `And that's a loss, folks! Beautiful. Look at that team, you're doing GREAT. Thanks for the fight. Now go make everyone out there wanna play too.`
- **Cerulean:**
  - intro: `Back, and the roster's stacked, and honestly so is yours. Numbers are up. ...You're the numbers, chat. You're why I do this.`
  - loss spin: `Two for two on camera, and I'm HERE for it. Clean beat. Thank you for being here, all of you. That's what matters.`
- **S.S. Anne:**
  - intro: `Luxury episode, chat. Big boat, big run. Still deathless. That's the brand. And you? You belong on this deck. Roll it.`
  - loss spin: `Losing in style! Frame it nice. That was gorgeous, challenger, thank you. The run goes on. It always does, and I'm glad you're on it.`
- **Pokemon Tower, Lavender (the glimpse):**
  - intro: `...Keep it down, chat. Show some respect. A nuzlocker's meant to FEAR a place like this. One death ends the whole run. That's the vow. ...Funny. Mine never seem to fall. And if they did... would anybody be here to see them go?`
  - loss spin: `...Clean fought. Thank you for that. Truly. ...You're still out there, right, chat? ...Yeah. Yeah. Thanks for staying. Let's move.`
- **Silph Co., Saffron:**
  - intro: `Still here, still recording. Light's just... blinking red at me now. Doesn't matter. I love this too much to stop. Where were we? Right. The run. And you, challenger, you're a joy to film. Let's go.`
  - loss spin: `Beaten again, live, no cuts, and I wouldn't trade it. Thank you for playing. Whoever's watching, or nobody, I'm still so glad I got to see THAT run. Keep the tape rolling.`
- **Route 22 (late):**
  - intro: `Final stretch, chat. All eight badges. Deathless, obviously. The vow held. And look at you, ready for the big one. So proud, honestly. Let's put on a show.`
  - loss spin: `Warm-up loss, doesn't count, and you EARNED it. Thank you. ...Even if the room's quiet, you filled it. Go finish this. Go be champion.`
- **Champion, Indigo (the landing):**
  - intro: `This is the one. Season finale. Whoever's out there watching, thank you. For the whole run. For playing at all. And challenger... thank you most. Okay. Roll it.`
  - loss / post: `...And that's a wrap. Beaten on camera, live, no edits, and it's PERFECT. You keep the run going now, you hear me? Go tell people to start theirs. ...Somebody's gotta remember this game, and I'm so glad it's you. Thank you for playing.`

## Per-encounter arc (mapped onto the 8 EXISTING rival fights, add/move nothing)

The built-in losing streak IS the arc: you beat him at every one of these, and he
reframes each loss as content AND as a reason to thank you, episode by episode. The
through-line is sincere love and gratitude, faintly shadowed by the unseen audience:
warm and encouraging throughout, brighter than ever early, the faint ache surfacing
once at Lavender, and a Champion beat where the warmth lands the character.

1. **Oak's Lab (Ep. 1, starter pick).** Sets up the warmth: he "goes live," frames
   the whole rivalry as his series, and greets you like the best thing to happen to
   the channel ("you're gonna be GOOD"). The tutorial loss becomes episode-one
   content AND his first thank-you. Bright, generous, no shadow yet.
   (Mechanically starter-only here, not a generated team, so keep it light setup.)
2. **Route 22 (early).** The show's on the road. He hypes you at the camera and
   celebrates the loss as your win, thanking you and urging the audience to go play
   too. All warmth, all encouragement.
3. **Cerulean.** He brags the roster's growing, but pivots to hyping YOURS and
   telling chat they're why he does this. Still glowing; the audience is beloved,
   not yet doubted.
4. **S.S. Anne (Vermilion).** The "luxury episode." He sells the deathless brand but
   folds you into it ("you belong on this deck"), thanking you for a gorgeous fight.
   Generous host energy throughout.
5. **Pokemon Tower (Lavender) - the glimpse.** A place of death. Amid the warmth,
   one quieter question surfaces: he preaches the sacred fear of the run, then
   wonders aloud whether anybody would be there to see his mons fall. It is the one
   beat where the faint ache shows plainly, but his gratitude carries it, he thanks
   the player and thanks chat for staying, then moves on. Play the quiet honestly;
   do not undercut it with a joke, but let the warmth, not hollowness, hold the page.
6. **Silph Co. (Saffron).** The channel's clearly gone quiet ("light's just blinking
   red"), and he keeps going anyway, because he LOVES this, not because he's empty.
   He says so, and calls the player a joy to film. The love of the game carries him
   when the audience won't. Warm and quietly the bravest beat.
7. **Route 22 (late).** All eight badges, deathless as promised, and he is PROUD of
   you, ready to hype the big one. A faint "even if the room's quiet" flickers, but
   he spends it on encouraging you to go be champion. Warmth load-bearing.
8. **Champion (Indigo) - the landing.** Season finale. He thanks whoever might be
   watching, sincerely, for the whole run and for playing at all, and thanks the
   player most. On the loss he calls it a wrap, hands YOU the run to carry, tells you
   to go get others to start theirs, and says it warm: "Somebody's gotta remember
   this game, and I'm so glad it's you." That is the character, landed: the whole
   documentary was love, love of the game, of chat, of the player, aimed at a room
   he could never quite see answer. This frames Oak's fixed capstone ("you forgot to
   treat your POKéMON with love and trust") gently: Locke's love ran to the RECORD
   and the audience more than the bond in his hands, so it's a nudge, not a verdict.
   Keep Oak's line untouched; Locke's arc just gives it a soft target.

**Rematch (post-game).** The channel never really ends, and he's delighted about it.
He is back, still filming, still thanking everyone, a re-run of a series he loves too
much to stop making. Light callback beat; keep the warmth up front, the ache faint,
the showman intact ("Back for the special edition, chat. So glad you're still here.").

## Release-safety notes

- **Homage, not likeness** [FLAG: release-swap]. The Documentarian is a composite of
  nuzlocke-streamer culture. No real handle, catchphrase, or signature bit. Keep the
  named-scene name-drops on Buhrito/Twitch; Locke stays the generic archetype so a
  release pass can genericize or remove him with a search, not a rewrite.
- **Keep him off the mandatory path.** He is a SELECTABLE rival identity; the game is
  fully playable without ever choosing him (Buhrito is the default). A release pass
  can cut Locke from the pick list without touching the plot.
- **Genericize-able by construction.** His comedy is the archetype (a streamer
  performing to phantom chat), not any one creator, so swapping the flavor to a
  neutral "self-narrating showoff" costs nothing. "The run," "deathless," "clip
  that," and "chat" all read in-world as a self-important performer talking to an
  audience; none require the real streaming scene to land.
- **No slang lock-in.** Unlike Sabrina's "absolute cinema" or the meme sign-offs,
  Locke's kit avoids dated one-liners on purpose, so no [FLAG: dated] is needed as
  written. If a specific meme is added later, tag it then.

## Consistency notes / tensions resolved

- **Tone rebalance (WARMTH IS CORE):** Locke's sincere positivity is the load-bearing
  center of the character, not a bit. He genuinely loves Pokemon, encourages the
  player and the audience, celebrates the player's wins over him, urges everyone to
  start their own run, and thanks people for playing / for being here (his signature
  note). The phantom-audience melancholy is now a FAINT UNDERTONE, not the thesis:
  just the small cost of aiming this much real love at a room he can't see answer. His
  support and gratitude are SINCERE, never a performance covering hollowness. Even the
  sad beats (Lavender, Silph) are mostly carried by his love of the game and his
  thank-yous, not by emptiness; at Silph he keeps going because he loves it.
- **Tonal control (style-guide §1, the whole job):** the comedy AND the warmth are
  quarantined to Locke's intros, loss-spins, and narration. His in-battle threat is
  real (kept counter-ace held for the finale, coverage team), so the hard-but-fair
  fight is not deflated. The Lavender glimpse and the Silph "dead channel" beat are
  played STRAIGHT, but warmth (not hollowness) holds the page.
- **Distributed fragments are constrained by the rival being a variable identity.**
  Town NPCs cannot name a rival whose identity differs per save (Buhrito / Twitch /
  Locke); vanilla rival gossip is generic ("your rival"). Any Locke-specific ambient
  fragment would need a VAR_RIVAL_ID branch on an existing NPC. So the Documentarian
  lives almost entirely in his OWN battle voice; distributed carriers are logged as
  IDEAS only (LOCKE-CAND), not committed.
- **Do NOT route Locke through Oak's nuzlocke gag.** The Oak arc keeps the nuzlocke
  fad IN-WORLD, UN-NAMED, and GENERIC ("some trainers"), and explicitly NEVER ties it
  to the rivals (see OAK-04 and the Oak consistency notes). Locke being "Father of the
  Nuzlocke" stays on Locke's own lines and the pick blurb; it must not leak into Oak's
  generic completionist bit.
- **Mechanics are locked; flavor conforms to them.** Never write a Locke line that
  claims his mons truly die, or that his team is fixed, or that he leads with his ace.
  The lore explains the mechanics as showmanship (ace saved for the finale; every
  season a fresh cast), it does not override them.

---

## Full rival dialogue (READY TO WIRE)

Final-ready per-beat lines, one string set per fight, presented like twitch.md's
"Full rival dialogue" section: gen-3 breaks inline (`\n` next line, `\l` scroll,
`\p` new textbox), `{PLAYER}`/`{RIVAL}` placeholders, terminate each string with `$`
when transcribed to the .inc. Two macro shapes drive the string count:

- `trainerbattle_earlyrival` beats need FOUR strings: INTRO, DEFEAT (player WINS),
  VICTORY (player LOSES), POST-BATTLE (after, player won).
- `trainerbattle_no_intro` beats need THREE strings: INTRO, DEFEAT (player WINS),
  POST-BATTLE (after, player won).

Arc holds: brash-warm early; the first faint "…right?" at Cerulean; over-warm
insistence at S.S. Anne; the ONE quiet glimpse at Lavender (played straight, no
joke on the page); performing-to-a-dead-channel-but-keeps-going-out-of-love at
Silph; load-bearing warmth at late Route 22; the Champion LANDS it warm and hands
off gracefully into Oak's fixed capstone. Fights keep their dignity: intros are
showman-warm, the gratitude and encouragement land in DEFEAT/POST after the battle.
No em dashes anywhere. [FLAG: release-swap] on the whole voice (homage-generic).

### 1. Oak's Lab (Ep. 1) - starter pick + tutorial battle
_Wiring note: map `PalletTown_ProfessorOaksLab_Frlg`, macro `trainerbattle_earlyrival` -> 4 strings (INTRO / DEFEAT / VICTORY / POST-BATTLE). Starter-only team here; keep it light setup._

- **INTRO:**
  `And we're LIVE, chat.` \n `Day one, fresh save.` \p
  `Say hi to the new` \n `challenger.` \p
  `…Oh, you are gonna` \n `be GOOD.`
- **DEFEAT (player wins):**
  `Ohh, we take the L` \n `on episode one!` \p
  `And what a beat.` \n `Give it up for the` \l `challenger.` \p
  `Thank you for playing.` \n `This is why I love` \l `this game.`
- **VICTORY (player loses):**
  `And that's the episode!` \n `Clean run, chat.` \p
  `But hey, YOU showed up.` \n `Thank you for that.` \p
  `…And we're clear.`
- **POST-BATTLE (player won):**
  `Go on, get out there,` \n `{PLAYER}.` \p
  `That's a future champ,` \n `chat. Believe it.` \p
  `…And we're clear.`

### 2. Route 22 (early) - road to the League
_Wiring note: map `Route22_Frlg`, macro `trainerbattle_earlyrival` -> 4 strings (INTRO / DEFEAT / VICTORY / POST-BATTLE)._

- **INTRO:**
  `Still rolling, chat.` \n `Look who followed us` \l `out of the lab.` \p
  `Camera's on YOU now,` \n `superstar.` \p
  `Show 'em what you've` \n `got.`
- **DEFEAT (player wins):**
  `And that's a loss,` \n `folks! Beautiful.` \p
  `Look at that team.` \n `You're doing GREAT.` \p
  `Thanks for the fight,` \n `{PLAYER}.`
- **VICTORY (player loses):**
  `That's the episode!` \n `We held the line.` \p
  `But you'll get there.` \n `I know it, chat.` \p
  `…And we're clear.`
- **POST-BATTLE (player won):**
  `Now go make everyone` \n `out there wanna play` \l `too.` \p
  `Thank you for being` \n `here. Roll it.`

### 3. Cerulean City - after the robbed house / Nugget Bridge
_Wiring note: map `CeruleanCity_Frlg`, macro `trainerbattle_no_intro` -> 3 strings (INTRO / DEFEAT / POST-BATTLE). The Bill nudge folds into POST-BATTLE; the separate Fame Checker handoff sub-beat (giveitem) stays its own scripted lines, unchanged here. First faint "…right?" undertone._

- **INTRO:**
  `Back, and the roster's` \n `stacked, chat.` \p
  `Honestly? So is yours.` \n `Numbers are up.` \p
  `…You're the numbers.` \n `You're why I do this.` \p
  `…right?`
- **DEFEAT (player wins):**
  `Two for two on camera,` \n `and I'm HERE for it.` \p
  `Clean beat, {PLAYER}.` \p
  `Thank you for being` \n `here. All of you.` \p
  `That's what matters.` \n `…That's what matters.`
- **POST-BATTLE (player won):**
  `Go north, chat sent me.` \p
  `The Bill guy shows off` \n `his rare mons for free.` \p
  `Great content. Go say` \n `hi.` \p
  `…And we're clear.`

### 4. S.S. Anne - 2F corridor
_Wiring note: map `SSAnne_2F_Corridor_Frlg`, macro `trainerbattle_no_intro` -> 3 strings (INTRO / DEFEAT / POST-BATTLE). CUT nudge lives in POST-BATTLE. Over-warm insistence._

- **INTRO:**
  `Luxury episode, chat!` \n `Big boat, big run.` \p
  `Still deathless. That's` \n `the brand.` \p
  `And you? You belong` \n `on this deck. Roll it.`
- **DEFEAT (player wins):**
  `Losing in style!` \n `Frame it nice.` \p
  `That was gorgeous,` \n `challenger. Thank you.` \p
  `The run goes on. It` \n `always does.` \p
  `And I'm so glad you're` \n `on it. Really. I am.`
- **POST-BATTLE (player won):**
  `There's a CUT master` \n `aboard. Go get CUT.` \p
  `Great for the show.` \p
  `Thank you for playing,` \n `{PLAYER}. Roll it.`

### 5. Pokemon Tower, Lavender - THE GLIMPSE
_Wiring note: map `PokemonTower_2F_Frlg`, macro `trainerbattle_no_intro` -> 3 strings (INTRO / DEFEAT / POST-BATTLE). Played STRAIGHT: warmth carries the page, do NOT undercut with a joke on any of these three strings._

- **INTRO:**
  `…Keep it down, chat.` \n `Show some respect.` \p
  `A nuzlocker's meant to` \n `FEAR a place like this.` \p
  `One death ends the` \n `whole run. That's the` \l `vow.` \p
  `…Funny. Mine never` \n `seem to fall.` \p
  `And if they did…` \p
  `would anybody be here` \n `to see them go?`
- **DEFEAT (player wins):**
  `…Clean fought.` \n `Thank you for that.` \p
  `Truly.` \p
  `…You're still out` \n `there, right, chat?` \p
  `…Yeah. Yeah.` \p
  `Thanks for staying.` \n `Let's move.`
- **POST-BATTLE (player won):**
  `…Go on, {PLAYER}.` \n `I'm right behind you.` \p
  `Thank you for being` \n `here. I mean it.`

### 6. Silph Co. 7F - Saffron
_Wiring note: map `SilphCo_7F_Frlg`, macro `trainerbattle_no_intro` -> 3 strings (INTRO / DEFEAT / POST-BATTLE). Giovanni nudge in POST-BATTLE. Dead-channel beat, played straight; love of the game holds it, not hollowness._

- **INTRO:**
  `Still here, chat.` \n `Still recording.` \p
  `The light's just…` \n `blinking red at me now.` \p
  `Doesn't matter. I love` \n `this too much to stop.` \p
  `Where were we? Right.` \n `The run.` \p
  `And you, challenger?` \n `You're a joy to film.` \p
  `Let's go.`
- **DEFEAT (player wins):**
  `Beaten again. Live,` \n `no cuts.` \p
  `And I wouldn't trade it.` \p
  `Thank you for playing.` \p
  `Whoever's watching…` \n `or nobody…` \p
  `I'm still so glad I got` \n `to see THAT run.`
- **POST-BATTLE (player won):**
  `Giovanni's up ahead.` \n `Go take his tower.` \p
  `Keep the tape rolling,` \n `{PLAYER}.` \p
  `Thank you for being` \n `here. Always.`

### 7. Route 22 (late) - rematch before Victory Road
_Wiring note: map `Route22_Frlg`, macro `trainerbattle_earlyrival` -> 4 strings (INTRO / DEFEAT / VICTORY / POST-BATTLE). All 8 badges. Warmth load-bearing._

- **INTRO:**
  `Final stretch, chat.` \n `All eight badges.` \p
  `Deathless, obviously.` \n `The vow held.` \p
  `And look at you.` \n `Ready for the big one.` \p
  `So proud, honestly.` \n `Let's put on a show.`
- **DEFEAT (player wins):**
  `Warm-up loss. Doesn't` \n `count. And you EARNED` \l `it.` \p
  `Thank you, {PLAYER}.` \p
  `…Even if the room's` \n `quiet…` \p
  `you filled it.`
- **VICTORY (player loses):**
  `That's the episode.` \n `We held on.` \p
  `But you're so close.` \n `Go again. I'll wait.` \p
  `…And we're clear.`
- **POST-BATTLE (player won):**
  `Go finish this.` \n `Go be champion.` \p
  `I'll be watching.` \n `Someone should be.` \p
  `Thank you for playing.` \n `Now go.`

### 8. Champion - Indigo Plateau - THE LANDING
_Wiring note: map `PokemonLeague_ChampionsRoom_Frlg`, macro `trainerbattle_no_intro` -> 3 strings (INTRO / DEFEAT / POST-BATTLE). POST-BATTLE precedes Oak's fixed capstone ("love and trust"); end on a graceful handoff. Do NOT rewrite Oak._

- **INTRO:**
  `This is the one, chat.` \n `Season finale.` \p
  `Whoever's out there` \n `watching… thank you.` \p
  `For the whole run.` \n `For playing at all.` \p
  `And challenger…` \n `thank you most.` \p
  `Okay. Roll it.`
- **DEFEAT (player wins):**
  `…And that's a wrap.` \p
  `Beaten on camera. Live.` \n `No edits.` \p
  `And it's PERFECT.`
- **POST-BATTLE (player won, before Oak enters):**
  `You keep the run going` \n `now. You hear me?` \p
  `Go tell people to start` \n `theirs.` \p
  `Somebody's gotta` \n `remember this game…` \p
  `and I'm so glad it's you.` \p
  `Thank you for playing.` \n `…And we're clear.`

### R. Rematch - post-game Champion
_Wiring note: map `PokemonLeague_ChampionsRoom_Frlg` (rematch entry), macro `trainerbattle_no_intro` -> 3 strings (INTRO / DEFEAT / POST-BATTLE). Light callback: warmth up front, ache faint, showman intact._

- **INTRO:**
  `Back for the special` \n `edition, chat!` \p
  `So glad you're still` \n `here.` \p
  `The channel never really` \n `ends, you know.` \p
  `I love this too much.` \n `Roll it, {PLAYER}.`
- **DEFEAT (player wins):**
  `Beaten again, and it` \n `never gets old.` \p
  `Thank you for the` \n `re-run.` \p
  `Best series I ever` \n `made.` \p
  `…And we're clear.`
- **POST-BATTLE (player won):**
  `Come back anytime.` \n `I'm always recording.` \p
  `Thank you for being` \n `here, {PLAYER}.` \p
  `Every single time.` \n `That's the episode.`

> READY TO WIRE. Voice locked to the Documentarian core above. The user or a build
> session branches each beat on VAR_RIVAL_ID to these Locke variants; text only here.
