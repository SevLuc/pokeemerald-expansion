# Progression

The critical path through Kanto: towns, gyms, story gates, and HM requirements
in order. Plot stays vanilla FRLG.

> STATUS: stub. Generate the baseline from vanilla data after the first build
> (trace map connections + story flags). Keep in sync with any change to gates.

## Order (vanilla FRLG baseline — fill in)
1. Pallet Town — starter, Oak's parcel
2. Viridian City → Route 1/2/22
3. Pewter City — **Gym 1: Brock** (Boulder Badge)
4. ... (Cerulean/Misty, Vermilion/Lt. Surge, Celadon/Erika, Fuchsia/Koga,
   Saffron/Sabrina, Cinnabar/Blaine, Viridian/Giovanni, Elite Four)

Gate note - Vermilion/Surge: the gym is gated behind HM01 Cut (vanilla: the
cuttable tree at Vermilion (19,24) is the only way into the gym pocket, and Cut
comes only from the S.S. Anne Captain). We reflavor this as Surge's "S.S. Anne
trial" - cross the ship, reach the Captain, earn Cut. No mechanical change to the
gate itself. See SURGE-GATE / SURGE-06 in docs/writing/lore-ledger.md.

## Level cap (hard, badge-gated)
Hard caps are ON (`B_EXP_CAP_TYPE = EXP_CAP_HARD`,
`B_LEVEL_CAP_TYPE = LEVEL_CAP_FLAG_LIST`, `B_RARE_CANDY_CAP = TRUE`). Over-cap
mons gain 0 battle EXP and Rare Candy is blocked at the cap. The cap is the
value for the first badge you have NOT yet earned, from the table in
`src/caps.c`:

| Progress point | Cap |
|---|---|
| Before Boulder (Brock) | 15 |
| Before Cascade (Misty) | 19 |
| Before Thunder (Surge) | 24 |
| Before Rainbow (Erika) | 29 |
| Before Soul (Koga) | 31 |
| Before Marsh (Sabrina) | 33 |
| Before Volcano (Blaine) | 42 |
| Before Earth (Giovanni) | 46 |
| Before Champion | 58 |
| Champion onward | 100 |

The field party menu also offers a `LEVEL` option (`LEVEL UP` / `LEVEL TO CAP`)
that levels a mon for free but never past the current cap.
