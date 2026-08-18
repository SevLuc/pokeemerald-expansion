# Brock - line bank (draft)

> Copy for the Pewter arc. Coy divorce/alimony reveal (decided with user).
> Index + gates live in ../lore-ledger.md (BROCK-01…10). Maps aren't wired yet,
> so these are staged here until placement in the relevant scripts.pory.
> Gen-3 rhythm: short two-line pages. Keep Brock's own battle lines archetypal.

## Layer 1 - Path to the gym (Pewter City / Route 2, UNGATED, deliberately vague)
Player should sense something's off without getting the punchline. Warm-but-sharp.

- Fond NPC: "Brock? Good man. Big heart. / ...Gives it away a little too easy, if you ask me."
- Wry NPC: "Here to challenge Brock? Get in line. / Everyone wants a piece of him. His lawyers, mostly."
- Woman: "Oh, I knew Brock. Briefly." (then walks off)
- Kid: "Mom says Brock's real generous. / Every single month, she says. I dunno what that means."

## Layer 2 - At the gym (phones gag → it clicks)
- Entry sting: IN-GAME. On entering the gym pre-badge, SE_POKENAV_CALL rings 3x
  and a box reads "The phones along the walls ring and ring... Nobody answers."
  (map ON_FRAME script, gated on FLAG_BADGE01_GET so it stops after you win).
- Gym guide: "Welcome! Don't mind the phones. / They ring a lot. Brock says to just let 'em ring."
- Trainer A: "Watch - a phone'll go off mid-battle and he won't flinch. / Man's got discipline. Or he knows exactly who it is."
- Trainer B: "Every phone in here's a different ringtone. / That's not decoration. That's a filing system."
- Reveal (guide or trainer, coy): "Six phones, six... let's call 'em 'previous sponsors.' / Rock-hard guy, soft heart."

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
- Return-visit line (BrockPostBattle): still vanilla, goofy rewrite pending.

## Layer 4 - Why he's a Gym Leader (POST-1st-badge, not on the path)
- NPC: "Ever wonder why Brock takes on every trainer who walks in? / Challenge fees. Alimony doesn't pay itself."

## Layer 5 - Late-game throwbacks (gated; just a couple)
- After ~6 badges: "Heard Brock's fielding challengers day and night now. / ...Heard he got married again, too. Connect the dots."
- Post-E4: "Brock's still at that gym. Still on the phone. / Some things are just eternal."
