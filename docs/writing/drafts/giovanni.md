# Giovanni - the man who was here all along (line bank / in-game)

> Viridian arc (Gym 8, GROUND, Earth Badge). Index/gates in ../lore-ledger.md
> (GIOVANNI-01..). Gen-3 rhythm: short two-line pages. NO em dashes.
> Giovanni is UNIQUE: unlike the seven leaders you meet once, he is the recurring
> antagonist you battle THREE times (Rocket Hideout -> Silph Co -> Viridian Gym)
> and hear about all game through Team Rocket. The lore rides on his real
> appearances plus a region-wide "absent leader" mystery.

## Concept / engine
- SURFACE (canon, untouched): the Team Rocket boss. His crime plot, the Master
  Ball deal, the disbanding, the Earthquake TM, all vanilla. The three battles
  stay straight and dangerous (hard-but-fair); humanity only leaks in defeat/post.
- HIDDEN LAYER (revealed by progression): the most-wanted man in Kanto has spent
  the whole game HIDING IN PLAIN SIGHT as the absent GYM LEADER of the sleepy
  first city you walked through. The region carries two absences, an unseen ROCKET
  BOSS and a never-there 8th GYM LEADER, and the fragments slowly rhyme them until
  the PLAYER (never the NPCs) connects that they are one man. Canon does the payoff
  for you: the gym is locked all game and only opens at the end.
- ENGINE (the "why", NO son thread - decided w/ user): the SELF-MADE MAN FROM THE
  DIRT. Giovanni came up from nothing; to him strength IS worth, and being weak
  once was terror. ROCKET and the hunt for "the strongest" is a poor kid's dread of
  ever being powerless again. GROUND-type is thematically exact: the man who dug
  everything out of the ground himself. When he finally loses, the empire was never
  the point (power was), so he gives it up without a fight and walks off to chase
  strength for its own sake ("dedicate my life to training", "bettering myself,
  none other").
- SILLY-THROUGH-CONTRAST: Viridian is an earnest little town whose one civic quirk
  is proud, defensive devotion to a LEADER nobody has ever met. A gym guide
  institutionalized at his post ("He's a busy man. He'll be in."), townsfolk sure
  their mystery leader is a lovely man, the door "locked, the LEADER away on
  business" (his business = crime). Dramatic irony: the danger stays straight in
  the three battles; the comedy is the whole town's civic blind spot around the
  empty gym.

## Delivery mode
- DOMINANT: the region-wide "who is the Viridian LEADER? / who is the ROCKET BOSS?"
  ambient mystery, coy, spread so the player rhymes the two absences.
- SPINE: the three battles reflavored to escalate the self-made + double-life
  weight (straight/menacing; engine leaks only in post-battle).
- PAYOFF: semi-plain, like Koga. Canon already lands "he was here all along" inside
  the gym (Gym Guy: "GIOVANNI was the GYM LEADER of VIRIDIAN?"; statue "LEADER: ?"
  -> "LEADER: GIOVANNI"). We extend it and add the self-made grace note in his own
  post-battle + the Fame Checker.
- The Fame Checker (in-game who's-who, 6 beats keyed to FAMECHECKER_GIOVANNI) is a
  built-in progressive-reveal vehicle; we reflavor its 6 flavor texts to carry the
  self-made / hidden-leader arc (the vanilla "red-haired kid" beat is repurposed
  to a self-made loner note, since there is no son thread).

---

## SPINE: the three battles

### 1. Rocket Hideout B4F (first meeting, ~after Rainbow Badge)
Player does NOT yet know he is a gym leader. Seed the self-made engine, stay
menacing.

`RocketHideout_B4F_Text_GiovanniIntro`
```
So! I must say, I am impressed you
got here.
I built TEAM ROCKET from nothing.
Strong POKéMON built the rest.
They are tools, and I take the tools
I need. That is how one gets strong.
I am the leader, GIOVANNI!
For your insolence, you will feel a
world of pain!
```

`RocketHideout_B4F_Text_GiovanniPostBattle`
```
I see. You raise POKéMON with care.
Care. I never had that luxury.
Where I come from, the weak are
ground under. So I made myself strong.
A child like you could not yet grasp
what I mean to achieve.
I shall step aside this time.
…We will meet again.
```
Defeat: "Nngh… impossible! Clawed up from nothing… for this?"

### 2. Silph Co 11F (second meeting, ~after Marsh Badge)
Lean into the legit-businessman veneer, the double life.

`SilphCo_11F_Text_GiovanniIntro`
```
Ah, {PLAYER}.
So we meet again.
The PRESIDENT and I are settling a
simple business matter.
A man can wear more than one face.
You would be amazed which mine open.
Keep your nose out of grown-up
matters…
Or taste a world of pain!
```

`SilphCo_11F_Text_GiovanniPostBattle`
```
Blast it all!
My plans for SILPH, ruined!
No matter. ROCKET will never fall.
I have climbed from far lower than this.
{PLAYER}. All POKéMON exist to make
their owner strong. Remember it.
I must go. But I shall return!
```
Defeat: "Arrgh!! Bested by the same brat, twice?!"

### 3. Viridian Gym (final, Earth Badge). THE REVEAL.
Canon reveals it here; we land "hidden in plain sight" + the self-made walk-away.
Keep every control code exactly.

`ViridianCity_Gym_Text_GiovanniIntro`
```
Fwahahaha!
Welcome to my hideout.
Or did you think a GYM an odd place
to find me?
I have stood in VIRIDIAN all along.
The LEADER no one ever met.
Hidden in plain sight, while I built
ROCKET up from nothing.
No more hiding. This time I hold
nothing back!
Once more, you shall face
GIOVANNI, the greatest TRAINER!{control codes preserved}
```

`ViridianCity_Gym_Text_GiovanniPostBattle`
```
Beaten in my own GYM.
I cannot face my followers now.
As of today, TEAM ROCKET is
finished. Forever.
I chased power my whole life. I
thought an empire was the road to it.
I was wrong. Strength is a road you
walk alone. I will walk it again.
From nothing, as I began.
Farewell!
```
Defeat (hands over the badge; control codes preserved): "Ha…! So the dirt breeds
strength after all. And you have won it. Take the EARTHBADGE. You tore it from me,
fair and true."
Earth Badge / TM26 also reflavored to the self-made + double-life voice ("Power
answers to the one who earns it."; "A parting gift, from the dirt I dug it out
of."; TM26: "The ground itself, turned into a weapon… I forged it when I first
held this GYM. …Before the other life.").

NOTHING of Giovanni's is left vanilla: all three intros, all three defeats, all
three post-battles, and the badge/TM lines are reflavored. The GYM TRAINERS
(Yuji/Atsushi/Jason/Kiyo/Warren/Takashi/Cole/Samuel) are also reflavored off their
vanilla karate/whip filler onto GROUND-grit + reverence for the self-made mystery
LEADER (fixes the vanilla oddity of a Ground gym voiced by Fighting-types); the
Gym Guy's canon "like GROUND-type" tip and the statue "LEADER: ?" -> "GIOVANNI"
flip are kept as functional payoff.

---

## AMBIENT: the two rhyming absences + civic devotion (appends only)

Placed by APPENDING to existing NPC/grunt lines. No new objects/art (per style
guide). Exact labels confirmed at wire-in; see the ledger for gates/order.

### Viridian City (the civic blind spot, UNGATED, pre-gym)
- `ViridianCity_Text_GymDoorsAreLocked` -> add "The LEADER is away… on business."
  (dramatic irony: his business is crime).
- `ViridianCity_Text_GymClosedWonderWhoLeaderIs` (the anchor) -> keep the wonder,
  add the proud-of-him-anyway devotion.
- Woman line append: "Our LEADER? Never met the man. …Lovely fellow, I'm sure."
- `ViridianCity_Text_ViridiansGymLeaderReturned` (fires when the gym unlocks, badge
  7, BEFORE you beat him) -> civic joy, "after all these years, I knew he'd come
  back!" (irony: they are thrilled their mystery leader is back, not knowing who).

### The unseen boss (Rocket beats, coy, rhymes with the absent leader)
Append a self-made / respectable-face note to existing grunt lines the player
already reads:
- Mt Moon (first brush): a grunt/Super Nerd note that the BOSS wants only the
  strongest, "came up from the dirt, they say."
- Rocket Hideout grunts: "The BOSS started with nothing. Nothing! Now look."
- Silph Co grunt (`SilphCo_11F_Text_Grunt1PostBattle` "My BOSS likes his POKéMON
  tough!") -> add "He had to be tough. Where he's from, soft things don't last."
- Lavender/Pokemon Tower Rocket: the ruthless beat (keep canon) + a grunt uneasy
  that the boss "has a straight-face life somewhere none of us have seen."
- Five Island Rocket Warehouse (post-game): the remnants; the boss is GONE, not
  for money, "gone to get strong. Alone. Like he started."

### Viridian Gym trainers (the payoff chorus, already half there in canon)
- Samuel: canon "closed a long time… our LEADER is back!" (kept).
- Jason: canon "Do you know the identity of our GYM LEADER?" (kept).
- Gym Guy: canon "Even I don't know the VIRIDIAN LEADER's identity… toughest of
  all… like GROUND-type." (kept) / post-victory "GIOVANNI was the GYM LEADER of
  VIRIDIAN?" (kept).
- Add ONE self-made grace note to a trainer post-battle (Warren/Kiyo): "They say
  the LEADER built himself up from nothing. …From the ground up."

### Fame Checker (FAMECHECKER_GIOVANNI, 6 beats, progressive)
The in-game who's-who unlocks 6 beats keyed to the encounters. ALL beats reflavored
to the self-made / hidden-leader arc (0 "from nothing"; 1 "trusts nothing but
strength"; 2 "hard as stone… people are tools too"; 3 "the LEADER no one ever met";
4 reveal "the ROCKET BOSS was our GYM LEADER all along?"; 5, formerly the red-hair
kid, now the self-made loner "came up from the gutter alone… no one has ever met
them"). The letter quote too ("I go back to the dirt I came from, to make myself
stronger. Alone."). No son thread survives. See ledger GIOVANNI-FAME.

---

## TODO
- Wire-in: confirm exact peripheral labels, place appends, keep page breaks in-box.
- Build + playtest to confirm the two-line rhythm reads on hardware.
- Balance (separate from lore): Giovanni's rebalanced GROUND team is still TBD;
  the Earth cap is 46. Gym 8 in ../../overview/gyms.md.
