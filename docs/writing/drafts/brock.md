# Brock - line bank (draft)

> Copy for the Pewter arc. Coy divorce/alimony reveal (decided with user).
> Index + gates live in ../lore-ledger.md (BROCK-01…10). Maps aren't wired yet,
> so these are staged here until placement in the relevant scripts.pory.
> Gen-3 rhythm: short two-line pages. Keep Brock's own battle lines archetypal.

## Layer 1 - Path to the gym (Pewter City, UNGATED, deliberately vague)
Player should sense something's off without getting the punchline. Warm-but-sharp.
Coy: "generous every month", "his lawyers", "briefly", "history" - none names a
divorce until the ringing phones at the gym make it click.
STATUS: drafted, not yet placed (user wires NPCs in Porymap; I write scripts then).
Carriers below note EXISTING Pewter City NPCs vs NEW objects to add.

- [Fat Man - EXISTING NPC, IN-GAME] appended to his Brock praise: "…Mind you,
  the man's got history. / You'll see soon enough."
- [Lass - EXISTING NPC, IN-GAME] replaced her Clefairy/Moon-Stone rumor: "BROCK?
  Everybody loves BROCK. / Big heart, that one. …Gives it away a little too easy."
- [NEW NPC near gym] "Off to challenge BROCK? Get in line. / Everyone wants a
  piece of him. His lawyers, mostly."
- [woman, then clams up] "Oh, I knew BROCK. Once. …Briefly."
- [adult gossip] "BROCK? Generous, they say. / Sends a payment every month, regular
  as clockwork. …To who? Best not to ask." (adult ex/alimony implication ONLY; do
  NOT frame this as a child, a kid's parent, or child support - keep minors out of
  the divorce arc entirely.)

## Layer 2 - At the gym (phones gag → it clicks) - ALL IN-GAME
- Entry sting: On entering the gym pre-badge, SE_POKENAV_CALL rings 3x and a box
  reads "The phones along the walls ring and ring... Nobody answers." (map
  ON_FRAME script, gated on FLAG_BADGE01_GET so it stops after you win).
- Gym Guy (guide) welcome: "Hey! Welcome to PEWTER GYM. / Don't mind the phones.
  BROCK says let 'em ring." (then keeps his party-order tip.)
- Gym Guy post-victory: kept VANILLA ("Just as I thought! / You're POKéMON champ
  material!") to avoid overusing the phones gag.
- Liam (trainer) intro: "Hear all these phones? Each one rings different. /
  That's not decoration. That's a filing system."
- Liam defeat (coy reveal): "Six phones out there. Six... let's call 'em
  'previous sponsors.'"
- Liam post-battle: "Soft heart, that BROCK. / Rock-hard everywhere else."

## Layer 3 - Brock himself (goofy-romantic surface, subtle divorce undertone)
FINAL intro, IN-GAME in PewterCity_Gym_Frlg/scripts.inc (PewterCity_Gym_Text_BrockIntro).
The phones interrupt his rambling; ends on the perfect wink that starts the battle.
- Intro:
  - "A challenger! Wonderful."
  - "Oh, the phones...? Let's just say I'm a very reachable man."
  - "ROCK taught me patience, kid. So did a marriage or two."
  - "Word of advice, kid. Always read the whole contract before you say 'I do'..."
  - "RING! RING! RING! RING! RING!"
  - "...Ignore that. Let's battle." (battle starts)
- Defeat: IN-GAME (PewterCity_Gym_Text_BrockDefeat). Goofy, keeps the badge
  fanfare + FLASH info; jokes: "Lost again. Same as my love life. / At least you
  didn't take half the GYM." / "Unlike a marriage, a BADGE is yours to keep." /
  closes on "RING! RING! RING! RING! / ...Ah, the phone. / ...I have to take
  this. Good luck." (bookends the intro's ring).
- TM39 hand-off hook (IN-GAME, PewterCity_Gym_Text_TakeThisWithYou): "Hold on,
  kid. A parting gift. / Ex-wives get the house. You get the TM." (NOTE: the one
  spot the divorce is stated outright, post-victory; everything else stays coy.)
  TM tutorial text itself left vanilla/functional.
- Return-visit line (IN-GAME, BrockPostBattle): "You again! / My lawyer says I
  can't afford a rematch." (dropped the vanilla Cerulean nudge.)

## Layer 4 - Why he's a Gym Leader (POST-1st-badge, not on the path)
- NPC: "Ever wonder why Brock takes on every trainer who walks in? / Challenge fees. Alimony doesn't pay itself."

## Layer 5 - Late-game throwbacks (gated; just a couple)
- After ~6 badges: "Heard Brock's fielding challengers day and night now. / ...Heard he got married again, too. Connect the dots."
- Post-E4: "Brock's still at that gym. Still on the phone. / Some things are just eternal."
