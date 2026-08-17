# Lore Ledger (keystone)

> Purpose: the master consistency map for distributed storytelling. Every history
> fragment revealed through an NPC gets one row so nothing contradicts and the
> story unlocks in a sensible order.
> Rule: add/update a row in the same PR as any new lore line.

## How to read a row
- ID — stable fragment id, e.g. BROCK-03.
- Subject — who/what the fragment is about.
- Reveal — what the player learns (one line).
- Source NPC — who says it (or object/sign).
- Map — where they are.
- Gate — progression condition (badge count, flag, story beat).
- Order — intended discovery order within the subject's arc.
- Status — idea / drafted / in-game.
- Flags — release/consistency tags from the style guide.

## Brock — "the phones" gag + history
Concept: Brock's gym is cluttered with phones; NPCs riff on him being "on call."
Optional, discoverable flavor that also smuggles in his backstory (a busy older
brother running the gym while minding his siblings). Uses existing vanilla
phone/PC objects only — no new art.

> Reference check: confirm the exact "Brock is calling" meme you're riffing on
> before finalizing wording — these rows capture the gag mechanic, not a verified
> meme canon.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| BROCK-01 | Brock (gag) | "Why does Brock keep so many phones in here?" | Gym guide | Pewter Gym | none | 1 | idea | — |
| BROCK-02 | Brock (gag) | Trainer jokes the phones never stop; Brock never picks up mid-battle. | Pewter Gym trainer | Pewter Gym | none | 2 | idea | — |
| BROCK-03 | Brock (history) | Brock raises his younger siblings — the calls are family checking in. | Pewter City NPC | Pewter City | after 1st badge | 3 | idea | — |
| BROCK-04 | Brock (history) | He took over the gym young when his father left to train. | Pewter NPC / sign | Pewter City | after 1st badge | 4 | idea | [FLAG: canon-check] |
| BROCK-05 | Brock (anime nod) | His real dream is breeding/cooking, not gym-leading. | Route 3 trainer | Route 3 | after 1st badge | 5 | idea | [FLAG: canon-check] |

Consistency notes:
- Keep BROCK-03/04 non-contradictory with any vanilla Pewter dialogue you retain.
- Gag (01–02) is available immediately; history (03–05) unlocks post-badge so it
  reads as "learning more after you've met him."

## Template: new gym leader
Copy per leader. Keep fragments optional and gated so a rushing player still
finishes and a curious one gets the hidden layer.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| XXXX-01 | <leader> | <hook the player notices first> | | | none | 1 | idea | — |
| XXXX-02 | <leader> | <deeper detail> | | | after Nth badge | 2 | idea | — |
| XXXX-03 | <leader> | <the payoff / reframe> | | | late-game flag | 3 | idea | — |

## Optional: in-world aggregator (decide later)
FRLG has no quest log, so players piece histories together from memory. If that's
too easy to miss, add a light aggregator — a gossip or librarian per town who
recaps what you've uncovered. Not committing yet; noted so it isn't forgotten.
