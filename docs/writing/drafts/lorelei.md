# Lorelei - line bank (in-game)

> Elite Four arc (Ice). Index/gates in ../lore-ledger.md (LORELEI-*). Gen-3
> rhythm: short two-line pages. No em dashes. The crusade + the LAPRAS rescue
> play STRAIGHT so the fight lands; the pop-culture pettiness (VANILLA, the ICE
> BUCKET CHALLENGE) is the comedy, scoped to her only.

## Elite Four delivery model (applies to all four)
The Elite Four cluster at Indigo and are fought back to back, with no town of
NPCs around each one. So their histories use the DISTRIBUTED model (like
Giovanni), seeded across the world, NOT the gym model (a home town leaking
gossip). Lorelei is the easy first case: she uniquely HAS a home region full of
NPCs, Four Island in the Sevii archipelago (canon FRLG), plus her doll house and
the Icefall Cave. Bruno / Agatha / Lance will each need their own seeding plan
(they have far fewer natural NPCs; TBD in later PRs).

## Concept / engine
- Lorelei is the ICE type's fiercest evangelist. Everyone "knows" Ice is a weak
  type: weak to nearly everything, resists almost nothing. She has built her
  whole life around disproving that.
- WHY (the hidden layer, revealed COYLY on Four Island, never by her): as a child
  she was drowning in the freezing sea off Four Island and a wild LAPRAS rose out
  of the cold and carried her home. She owes the type her life. Her Elite Four
  ace is a LAPRAS (Lv 54, her joint-highest), so the reveal quietly rhymes with
  the mon on her team and the bald LAPRAS doll enshrined in her house.
- The seriousness IS the joke (silly-through-contrast): she is deadly earnest
  about Ice's honor, and nurses specific petty grudges against anything that makes
  the type look weak, above all a soft no-account she only calls "VANILLA."
- Mystique rule: NPCs mention the cold sea, the thing that rose from it, the
  LAPRAS doll, the grudge list. NOBODY says "a Lapras saved her and now she has a
  complex." The player connects it.

## Battle voice (LOCKED: Option A, full voice)
Her own lines carry the crusade + the gags; the loss stays straight (joke on the
way in, dead straight on the way out, so the fight carries weight).

- INTRO (replaces vanilla Text_Intro):
  "Welcome to the POKéMON LEAGUE.\p
   I am LORELEI of the ELITE FOUR.\p
   The world calls ICE the weakest\n
   type. Fragile. A punch line.\p
   I have given my life to proving\n
   the world wrong.\p
   Consider this your ICE BUCKET\n
   CHALLENGE, trainer.\p
   If your notion of ICE is something\n
   soft and VANILLA… be corrected."
- DEFEAT (keep vanilla Text_Defeat unchanged): "…Things shouldn't be this way!"
- POST-BATTLE (replaces vanilla Text_PostBattle):
  "You are strong. I felt it.\p
   But mark this: you did not defeat\n
   ICE today. You defeated ME.\p
   The type is not weak.\n
   I am simply not yet finished.\p
   Go on. The others await."
- REMATCH INTRO (Champion rematch, replaces vanilla Text_RematchIntro): same
  crusader framing, shortened; keep the ICE BUCKET / VANILLA beat as a callback.

## Distributed history (Four Island + Indigo reception)
Coy fragments, existing NPCs/objects only, no new art/beats. Full table + gates
in ../lore-ledger.md (LORELEI-01..10).
- Indigo reception: the crusade is legend (01); post-defeat callback (09).
- Four Island town: the cold-sea rescue, coy (02); the "won't hear a bad word"
  crusade (03); the fierce-defender note after the Rocket beat (07); the grudge
  list + VANILLA, coy and funny (08).
- Lorelei's House: the LAPRAS doll shrine (reflavor the existing doll object, 04);
  her vanilla "island where I was born" lines logged as-is (05).
- Icefall Cave: "this is where it happened," coy (06).

## Release flags
- VANILLA and the ICE BUCKET CHALLENGE are real-world nods: tag [FLAG: dated]
  (memes date) and [FLAG: release-swap] (VANILLA winks at a real person).
- Built to survive a strip: "VANILLA" already reads in-world as bland, weak ice,
  and the bucket line generalizes to plain ice water. The LAPRAS rescue and the
  Ice crusade carry no flags.

## TODO (still open)
- Confirm exact reception NPC(s) at Indigo Plateau (PokemonLeague_1F) for 01/09;
  a new NPC is acceptable per the ledger if none fits.
- Placement pass: append/branch the Four Island + Icefall Cave lines onto existing
  NPCs; reflavor the Lorelei's House doll object (04) in scripts.pory / text.
- Balance (separate from lore): rebalanced Elite Four teams still TBD.
- Data note (out of scope for this lore PR): TRAINER_ELITE_FOUR_LORELEI has
  `Gender: Male` in trainers_frlg.party, a vanilla quirk affecting the mugshot.
  Flagged only; not changed here.
