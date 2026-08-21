# Intro + Rival select (PARKED)

STATUS: parked mid-design. Revisit AFTER the other characters. The rivals will
get personalized, full arcs written by the user, so Phase 2 personalities are
intentionally deferred. Nothing here is in-game yet.

## New-game intro flow (decided)
1. Author welcome (replaces the Oak-speech welcome text; prepend to
   gOakSpeech_Text_WelcomeToTheWorld so it needs NO code, then flows into Oak).
   The professor sprite still shows -> he becomes the silent "narrator".
2. "What's your name?" (vanilla, kept)
3. Pre-rival framing text (NEW, to write) - the "pick your nuzlocker rival" setup
4. Rival pick - 2 forced options (no custom entry)

## Author welcome draft (GAME NAME: "Funky Red" - provisional / "for now")
Casual, old-school, no em dashes, "^^" dropped (won't render in gen-3 font):

  "Hi there! Welcome to FUNKY RED."   (provisional name; final caps TBD at wiring)
  "This one's made for casual, old-school POKéMON fun."
  "Fire beats grass, grass beats water, and bug beats… whatever."
  "No setup moves. No held items. No mickey mouse strategies."
  "For the rest, play by whatever rules you like."
  "Hope you have a great time!"

## Rivals (locked names): Buhrito · Twitch
- FIRST VERSION: only 2 rivals, Buhrito and Twitch. Pchal is dropped for v1
  (may return in a later version; not committing to it now).
- Streamer/nuzlocker homages -> [FLAG: release-swap] (genericize before any public release).
- "Twitch" (6 chars) chosen over "Twitch Chat" (11) to fit the 7-char name cap;
  both names fit the normal name system.
- Selection is FORCED (no "NEW NAME" custom entry).
- Full personalities: each rival gets distinct dialogue across every rival
  encounter (Oak's Lab, Route 22, Cerulean, S.S. Anne, Pokémon Tower, Silph Co.,
  Route 22 rematch, Champion). User will write these personalized later.

## Implementation notes for later
- Phase 1 (system + intro): forced 2-option pick that stores a choice var
  (e.g. VAR_RIVAL_ID) AND sets {RIVAL}; author welcome + pre-rival text. The pick
  menu already exists in src/oak_speech.c (sRivalNameChoices[], FIRERED branch =
  Green/Gary/Kaz/Toru) - swap to the 2 streamers + add their gNameChoice_*
  strings in data/text/new_game_intro_frlg.inc. Small C edit, needs sign-off.
- 7-char name cap (PLAYER_NAME_LENGTH) is a hard practical limit for typed names
  (save layout + UI). Not raising it. If a rival name ever needs >7 chars, route
  display through ExpandPlaceholder_RivalName by choice var instead.
- Phase 2 (personalities): branch each rival encounter script on VAR_RIVAL_ID.
- GAME NAME: "Funky Red" (provisional, set by user "for now"). Referenced in-game by
  Buhrito's Champion intro. CLAUDE.md title updated. STILL TO UPDATE when adopted for real:
  the actual in-game intro welcome string (currently only drafted here).
