# Lore Ledger (keystone)

> Purpose: the master consistency map for distributed storytelling. Every history
> fragment revealed through an NPC gets one row so nothing contradicts and the
> story unlocks in a sensible order.
> Rule: add/update a row in the same PR as any new lore line.

## How to read a row
- ID - stable fragment id, e.g. BROCK-03.
- Subject - who/what the fragment is about.
- Reveal - what the player learns (one line).
- Source NPC - who says it (or object/sign).
- Map - where they are.
- Gate - progression condition (badge count, flag, story beat).
- Order - intended discovery order within the subject's arc.
- Status - idea / drafted / in-game.
- Flags - release/consistency tags from the style guide.

## Brock - "the phones" gag + serial-divorcé history
Concept: Brock's gym is cluttered with ringing phones. Surface gag: he's always
"on a call" (the "Brock is calling" meme). The hidden layer, revealed COYLY: the
phones are his ex-wives, and he runs the gym mostly for the challenge fees -
alimony doesn't pay itself. Engine of the joke = the anime "hopeless romantic"
Brock: he keeps falling in love, keeps marrying, keeps divorcing, keeps paying.
Uses existing vanilla phone/PC objects only - no new art.

Reveal is COY throughout (player choice): NPCs never say "divorce" or "ex-wife"
outright. They say "previous sponsors," "generous every single month," ringtones
as a "filing system." The player connects the dots. Brock himself plays it
straight (one wink) so the FIGHT still lands.

> Reference check: the "Brock is calling" bit rides on the meme + the anime
> womanizer trait. Keep all wording in our own voice - no verbatim anime lines.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| BROCK-01 | Brock (path, vague) | Lass: "Big heart, that one. Gives it away a little too easy." | Lass (existing) | Pewter City | none (pre-gym) | 1 | drafted | - |
| BROCK-02 | Brock (path, vague) | Fat Man (append to his Brock praise): "Mind you, the man's got history. You'll see." | Fat Man (existing) | Pewter City | none (pre-gym) | 2 | drafted | - |
| BROCK-03 | Brock (path, vague) | "Off to challenge BROCK? Everyone wants a piece of him. His lawyers, mostly." | new NPC near gym | Pewter City | none (pre-gym) | 3 | drafted | - |
| BROCK-03b | Brock (path, vague) | Woman: "Oh, I knew BROCK. Once. …Briefly." | new NPC (woman) | Pewter City | none (pre-gym) | 3 | drafted | - |
| BROCK-03c | Brock (path, vague) | Kid: "Mom says BROCK's real generous. Every single month. I don't get it." | new NPC (kid) | Pewter City | none (pre-gym) | 3 | drafted | - |
| BROCK-04 | Brock (gag) | Gym guide: the phones ring constantly; Brock says just let 'em ring. | Gym guide | Pewter Gym | none | 4 | in-game | - |
| BROCK-05 | Brock (gag) | Trainer (Liam): each phone has its own ringtone, "that's a filing system." | Pewter Gym trainer | Pewter Gym | none | 5 | in-game | - |
| BROCK-06 | Brock (reveal, coy) | Trainer (Liam) on defeat: "Six phones, six... 'previous sponsors.'" | Pewter Gym trainer | Pewter Gym | none | 6 | in-game | [FLAG: canon-check] |
| BROCK-07 | Brock (intro) | Goofy-romantic ramble ("a marriage or two"; contract advice) cut off by ringing phones, then "...Ignore that. Let's battle." | Brock | Pewter Gym | none | 7 | in-game | [FLAG: canon-check] |
| BROCK-08 | Brock (why leader) | "Ever wonder why he takes on every trainer? Challenge fees. Alimony doesn't pay itself." | Pewter City NPC | Pewter City | after 1st badge | 8 | drafted | [FLAG: canon-check] |
| BROCK-09 | Brock (throwback) | "Heard he's fielding challengers day and night. Heard he got married again, too." | later-town NPC | TBD | after ~6th badge | 9 | idea | [FLAG: canon-check] |
| BROCK-10 | Brock (throwback) | "Brock's still at that gym. Still on the phone. Some things are eternal." | later-town NPC | TBD | post-E4 | 10 | idea | - |

Consistency notes:
- Path fragments (01-03) are UNGATED and pre-gym, and stay vague so the punchline
  only clicks once the player reaches the gym and sees the phones (04-07).
- Reveal never states "divorce/ex-wife" - coy euphemism only (decided w/ user).
- Why-leader (08) and throwbacks (09-10) unlock post-progression as callbacks.
- Brock's own battle lines stay archetypal Gym-Leader; comedy lives in the room
  around him, not in his threats, so the hard-but-fair fight still reads as real.
- RETIRED earlier draft: "raising younger siblings / father left to train."
  Replaced by the divorce/alimony arc. The anime hopeless-romantic trait is the
  only kept thread (it powers the divorces).

## Template: new gym leader
Copy per leader. Keep fragments optional and gated so a rushing player still
finishes and a curious one gets the hidden layer.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| XXXX-01 | <leader> | <hook the player notices first> | | | none | 1 | idea | - |
| XXXX-02 | <leader> | <deeper detail> | | | after Nth badge | 2 | idea | - |
| XXXX-03 | <leader> | <the payoff / reframe> | | | late-game flag | 3 | idea | - |

## Optional: in-world aggregator (decide later)
FRLG has no quest log, so players piece histories together from memory. If that's
too easy to miss, add a light aggregator - a gossip or librarian per town who
recaps what you've uncovered. Not committing yet; noted so it isn't forgotten.
