# Misty - line bank (draft)

> Cerulean Gym arc. Index/gates in ../lore-ledger.md (MISTY-01..). Not in-game yet.
> Gen-3 rhythm: short two-line pages. No em dashes.

## Concept / engine
- Tomboy, serious, wants to be seen as a real force. Youngest of the Sensational
  Sisters (they do the water SHOWS; she does the actual BATTLING) - chip on the
  shoulder about not being "just a dancer".
- PSYDUCK is her FIRST POKéMON. She's deeply attached, can't let it go, loves it,
  and it drives her crazy because it's everything she is NOT: whimsical, silly.
- THE REVEAL (payoff): because PSYDUCK keeps running off and acting dumb, she
  went all-in on WATER types... because water types can't run away. They're stuck
  in the pool with her.
- Cerulean respects her as an incredibly strong LEADER. They tease the bug thing
  ("just don't bring bugs, haha") and treat PSYDUCK as a beloved town jester -
  funny, annoying, tolerated.
- GIMMICK: no BUG-type POKéMON allowed in the gym. Gym guide blocks you at the
  door and explains (small party-type-check script; only code piece).

## Misty herself (Psyduck woven into her battle voice)
Intro - NO explanation. She builds to a battle cry, reaches for her strongest,
and PSYDUCK barges out instead (her reaction = the joke); battle starts instantly
and PSYDUCK is her actual lead in the fight.
- "So you're my next challenger."
- "I'm MISTY. Youngest of the Sensational Sisters."
- "They do the dance shows. I do the actual battling."
- "My policy? All-out offensive. All WATER. No mercy."
- "Prepare yourself. I'm sending out my strongest-"
- "*ploop!*" (with an inline {PLAY_SE SE_BALL_OPEN} ball-open sound; the text shows
  too, for muted players)
- "PSYDUCK?!" (battle starts)

BATTLE-OPEN SLIDE (in-game, trainer-slide TRAINER_SLIDE_BEFORE_FIRST_TURN): the
moment the fight opens with PSYDUCK on the field, Misty's pic slides in with a
gripe: "Fine. We do this with PSYDUCK. Don't you DARE go easy on me." (line is
easily swappable). NOTE: the ball IS still tossed for her lead - kept on purpose
(reframed: she confidently throws for her ace, Psyduck flops out). A true
no-ball "wild-style" send-out would need an untested battle-intro engine change.

BATTLE TEAM (in-game): PSYDUCK (Lv16, lead) + Staryu (Lv18) + Starmie (Lv21).
PSYDUCK is her comic opener (Water Gun / Disable / Tail Whip / Confusion). Adding
it as a 3rd body keeps the fight from getting easier - Staryu + Starmie still
follow. Level/moves are tunable.

Defeat (tough girl concedes; optional Psyduck cameo):
- "Ugh! Fine. You got me."
- "You're strong. I'll admit that. ...Don't let it go to your head."
- "Here. The CASCADEBADGE. You earned it."
- (option) "...Even PSYDUCK looks impressed. And PSYDUCK is NEVER impressed."

## Bug-ban gate (IN-GAME, gym gimmick)
On entering the gym, an ON_FRAME map script calls the new special
`PartyHasBugType`. If any party mon is a BUG type, the Gym Guy walks over, tells
you off, and shoves you back out to the city gym door. Message: "Whoa there! Is
that a BUG POKéMON? …Yeah, no. Not in MISTY's gym. One BUG in here and she's up
on a chair for the afternoon. Leave it outside. Then we'll talk." Works for any
party (even 6 bugs - the guide just tells you). EGGs are judged by their hatch
species (uses MON_DATA_SPECIES), so a bug-type egg is blocked too and can't hatch
inside. Always-on (could gate on FLAG_BADGE02_GET if the post-victory bounce ever
feels annoying).
Code: src/script_pokemon_util.c (PartyHasBugType) + data/specials.inc +
CeruleanCity_Gym_Frlg/scripts.inc (ON_FRAME BugCheck + Gym Guy walk/shove
choreography). No new art or map objects. NOTE: choreography is untested here
(no compiler); the guide's exact steps near the entrance may need a tweak in
mGBA/Porymap.

## Lore delivery - SUBTLE, spread over the road (not on the nose)
Principle: imply, never explain. The player pieces it together. Beats escalate as
you travel Cerulean City -> Nugget Bridge (Route 24) -> Route 25 (to Bill's). The
mandatory route trainers carry it; Diana/Luis at the gym only verify/entertain.

CERULEAN CITY (ambient, pre-gym):
- Respect (MISTY-01): "She runs that gym alone. Has for years. ...Say what you
  want about her."
- Jester (MISTY-03): "You'll spot a PSYDUCK around town. Answers to no one.
  ...Not even her."

NUGGET BRIDGE / Route 24 (mandatory gauntlet):
- Cale, the BUG CATCHER (MISTY-02, bug irony): post-battle "Me? I keep to the
  routes. That gym and I have an… understanding." (never says 'bugs banned'; a
  bug catcher who can't enter says it for us)
- Reli or Ali (MISTY-04, long bond): "That PSYDUCK's older than her badges.
  Was here before the gym was hers."
- Shane (frustration + love, no explanation): "Seen her scream at that duck.
  Seen her wait up half the night when it wanders off. ...Same duck."

ROUTE 25 (to Bill's, the subtle payoff - MISTY-05):
- A trainer near Bill's: "Ever notice she only trains what can't leave the
  water? ...She learned that chasing something that could." (player connects it
  to the runaway Psyduck; never stated)

GYM - Diana & Luis just VERIFY / ENTERTAIN (light, per user):
- Diana: "Oh, you've heard about the duck. Everyone has. …Don't bring it up."
- Luis: "You got this far, so you know the rule about bugs. …Good."

## BILL = the payoff aggregator (IN-GAME, Route 25 Sea Cottage)
Fused intro (before you free him, IN-GAME, both pal/lady copies): goofy, leans
into the CLEFAIRY - "Hiya! Behold, a majestic CLEFAIRY! / …I have a PhD, you
know. / BILL. Genius. Inventor. Presently a pink puffball that goes 'clef.' /
Bad experiment. Got fused. The CLEFAIRY seems thrilled. I am NOT. / Help me
un-fuse before it makes me do the little moon dance again."

The whole coy chorus pays off at Bill. After you free him from the CLEFAIRY, he
explains it all (the ONE deliberate non-coy telling): Misty's PSYDUCK wandered
into his Cell Separation System, mashed buttons, fused him, then walked out. He
finds it hilarious, then tells the Misty lore - Psyduck is her first mon and her
opposite ("MISTY's all discipline… and that PSYDUCK? Peak serenity, zero
thoughts"); since her first mon kept waddling off, she went all-in on POKéMON
that can't run off, and years in the pool made her a true master; then frames
the S.S. TICKET as thanks ("go take a cruise"). The free monologue does NOT
mention it; the deadpan verbal tic "…Don't ask me why the machine was set to a
CLEFAIRY" lands only on the RE-TALK (S.S. Anne line) and the LATER re-talk (the
rare-mons PC line).

## Post-badge emotional core (MISTY-06, gated, still implied)
- "Everyone thinks that PSYDUCK is the joke. …I think it's the one thing she'd
  never replace."

## THE CHORUS (whole-area gag): EVERY NPC/trainer drops one tiny oblique line
Concept: the entire Cerulean area quietly orbits Misty + the PSYDUCK (and maybe
an EGG). Each line is tiny, vague, and self-contained; the comedy is cumulative -
by the time you reach the gym you realize the whole town can't stop half-mentioning
her duck. Keep every line SUBTLE and VARIED (never repeat the same beat).
- Each route trainer: keep their INTRO as their own character; replace their
  POST-BATTLE line with one oblique Misty/Psyduck (or deniable "egg") flavor drop.
- TOGEPI stays deniable: only ever "an EGG" / "something she guards" until the
  user commits Togepi's arc. No Togepi by name yet.
- Angles to rotate so it never feels repetitive: the duck's escapes, its blank
  stupidity, the bug rule, her running the gym solo, the sisters/looks, her only
  ever training water, a mysterious egg, her chasing the duck cross-country.

Sample tone (spread across zones) - lock this before mass-producing the rest:
- City NPC: "She runs that gym alone. Has for years."
- City NPC: "That PSYDUCK answers to no one. Not even her."
- Timmy (Route 24): "Careful by the water. Things fall in. Ducks, mostly."
- Cale, bug catcher (Route 24): "Me and that gym have an… understanding."
- Reli (Route 24): "That duck's older than her badges."
- Ali (Route 24): "Found an EGG by the pool once. She took it so fast."
- Shane (Route 24): "Seen her wait up half the night for that duck. Every time."
- Route 25 trainer (near Bill): "She only trains what can't leave the water.
  …Wonder why."
- Beauty (Route 25): "Her sisters got the looks. She got… the other thing."
- Diana (gym, verify): "You've heard about the duck. Everyone has."
- Luis (gym, verify): "You know the rule about bugs by now. Good."
