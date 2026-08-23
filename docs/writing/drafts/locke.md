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

The self-styled star of a stream nobody can confirm is airing: Locke narrates his
whole run to a phantom chat, performs even his losses as content, and reveres "the
run" as sacred ritual, while quietly wondering if anyone is watching at all.

## The concept: The Documentarian

Locke is always RECORDING THE RUN. Every battle is an "episode" for a stream / an
audience that may or may not exist. He narrates his own fights (including his
defeats) as content, performing to a chat he addresses directly but never hears
back from.

**The engine (silly-through-contrast):** relentless upbeat showman patter for the
camera vs. a quiet emptiness underneath. The joke is the performance; the heart is
the question the performance is built to avoid ("...is anyone actually watching?").
Two straight men hold the comedy up:
- He genuinely REVERES "the run" as a sacred vow (permadeath, deathless, one life).
  That sincerity is the straight man to his own carnival-barker delivery.
- The phantom audience is the straight man to his hype. The louder the sell, the
  more you notice the silence answering it.

Keep it MOSTLY FUNNY. The pathos only peeks through in glimpses, never mawkish,
never a speech. He would rather die than let the bit drop, so the sadness leaks
around the edges of the bit, not through a confession.

## Locked voice + release flag

- **Streamer-homage NPC** [FLAG: release-swap]. Cocky, mythologizing, "the run" is
  scripture. Style-guide example feel: "One death and the whole run's over. I do
  NOT lose. ...probably."
- Verbal kit: "we're LIVE," "chat," "clip that," "great content," "the run,"
  "deathless," "the vow," "roll it," "that's a wrap," a gracious-host spin on every
  loss ("beautiful," "struggle sells," "the people love an underdog arc"). He talks
  TO the camera and ABOUT himself in showrunner terms (episode, season finale, arc).
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
  - intro: `And we're LIVE. Day one, fresh save. Say hi to the new challenger, chat. ...You'll do.`
  - loss spin: `Ohh, we take the L on episode one. Clip it. Honestly? Great content. Everybody loves an underdog arc.`
- **Route 22 (early):**
  - intro: `Still rolling, chat. Look who followed us out of the lab. Camera's on you. Try to be interesting.`
  - loss spin: `And that's a loss, folks. Beautiful. Struggle sells. Trust me on this.`
- **Cerulean:**
  - intro: `Back, and the roster's stacked. Numbers are up. ...The numbers are up, right?`
  - loss spin: `Two for two on camera. Cool, cool. ...Chat's still here, so. That's what matters.`
- **S.S. Anne:**
  - intro: `Luxury episode, chat. Big boat, big run. Still deathless. That's the brand. ...Not one.`
  - loss spin: `Losing in style, at least. Frame it nice. The run goes on. The run always goes on.`
- **Pokemon Tower, Lavender (the glimpse):**
  - intro: `...Keep it down, chat. Show some respect. A nuzlocker's meant to FEAR a place like this. One death ends the whole run. That's the vow. ...Funny. Mine never seem to. Nobody's around to see them go.`
  - loss spin: `...Clip that one. If anyone's out there. ...You're out there, right? ...Right. Let's move.`
- **Silph Co., Saffron:**
  - intro: `Still here. Still recording. Even if the light's just... blinking red at me now. Where were we. Right. The run.`
  - loss spin: `Beaten again, live, no cuts. ...I keep the tape rolling. Somebody's gotta.`
- **Route 22 (late):**
  - intro: `Final stretch, chat. All eight badges. Deathless, obviously. The vow held. ...Somebody write that down. Please.`
  - loss spin: `Warm-up loss, doesn't count. ...Nothing counts if the room's empty. ...Forget I said that. Onward.`
- **Champion, Indigo (the landing):**
  - intro: `This is the one. Season finale. Whoever's out there watching... thank you. For the whole run. Really. ...Okay. Roll it.`
  - loss / post: `...And that's a wrap. Beaten on camera, live, no edits. ...Perfect, actually. You keep the run going now. I'll keep filming it. ...Somebody's gotta remember it happened.`

## Per-encounter arc (mapped onto the 8 EXISTING rival fights, add/move nothing)

The built-in losing streak IS the arc: you beat him at every one of these, and he
reframes each loss as content, episode by episode. The phantom-audience thread runs
underneath: brash and sure early, subtly hollow by the later fights, one real glimpse
at Lavender, and a Champion beat that lands the character.

1. **Oak's Lab (Ep. 1, starter pick).** Sets up the bit: he "goes live," frames the
   whole rivalry as his series, calls you "the challenger" like casting a co-star.
   The tutorial loss becomes episode-one content. Fully brash; no cracks yet.
   (Mechanically starter-only here, not a generated team, so keep it light setup.)
2. **Route 22 (early).** The show's on the road. He directs you at the camera ("try
   to be interesting"). Spins the loss as underdog-arc storytelling. Still all sell.
3. **Cerulean.** Peak brag: the roster's growing, "numbers are up." First hairline
   crack, a tacked-on "...right?" that he talks straight past. The audience is
   starting to be something he ASSERTS rather than sees.
4. **S.S. Anne (Vermilion).** The "luxury episode." Leans hard on the deathless
   brand ("that's the brand. ...Not one."). The over-insistence is the tell; the
   more he sells the vow, the more you hear him reassuring himself.
5. **Pokemon Tower (Lavender) - the glimpse.** A place of death. The permadeath
   bravado meets something quieter: he preaches the sacred fear of the run, then
   admits, half to the camera, that his mons never actually fall and nobody is
   around to witness them if they did. This is the one beat where the emptiness
   surfaces plainly, then he snaps the bit back up and moves on. Play the crack
   straight; do not undercut it with a joke on the same page.
6. **Silph Co. (Saffron).** He is visibly performing to a dead channel now ("the
   light's just blinking red at me"), and keeps going anyway. The devotion to the
   run is what carries him when the audience clearly won't. Quietly the bravest beat.
7. **Route 22 (late).** All eight badges, deathless as promised, and he needs it
   RECORDED ("somebody write that down. Please."). The hype is intact but load-
   bearing; the run is the only thing holding him up.
8. **Champion (Indigo) - the landing.** Season finale. He thanks whoever might be
   watching, sincerely, for the whole run. On the loss he calls it a wrap, hands YOU
   the run to carry, and says the quiet part once: "Somebody's gotta remember it
   happened." That is the character, landed: the whole documentary was never about
   an audience. It was about being remembered. This frames Oak's fixed capstone
   ("you forgot to treat your POKéMON with love and trust") from a new angle: Locke
   loved the RECORD of them more than the bond, and it left him alone at the top.
   Keep Oak's line untouched; Locke's arc just gives it a target.

**Rematch (post-game).** The channel never really ends. He is back, still filming,
still narrating, a re-run of a series he can't stop making. Light callback beat;
keep the melancholy faint and the showman intact ("Back for the special edition,
chat. ...You never left, did you.").

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

- **Tonal control (style-guide §1, the whole job):** the comedy is quarantined to
  Locke's intros, loss-spins, and narration. His in-battle threat is real (kept
  counter-ace held for the finale, coverage team), so the hard-but-fair fight is not
  deflated. The Lavender crack and the Silph "dead channel" beat are played STRAIGHT.
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
