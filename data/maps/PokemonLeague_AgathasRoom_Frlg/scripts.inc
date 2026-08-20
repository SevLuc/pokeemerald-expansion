PokemonLeague_AgathasRoom_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_AgathasRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, PokemonLeague_AgathasRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PokemonLeague_AgathasRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_AgathasRoom_OnFrame
	.byte 0

PokemonLeague_AgathasRoom_OnResume::
	setvar VAR_0x8004, 2
	call PokemonLeague_EventScript_DoLightingEffect
	end

PokemonLeague_AgathasRoom_OnLoad::
	call_if_set FLAG_DEFEATED_AGATHA, PokemonLeague_AgathasRoom_EventScript_SetDoorOpen
	call_if_eq VAR_MAP_SCENE_POKEMON_LEAGUE, 3, PokemonLeague_AgathasRoom_EventScript_CloseEntry
	end

PokemonLeague_AgathasRoom_EventScript_CloseEntry::
	call PokemonLeague_EventScript_CloseEntry
	return

PokemonLeague_AgathasRoom_EventScript_SetDoorOpen::
	call PokemonLeague_EventScript_SetDoorOpen
	return

PokemonLeague_AgathasRoom_OnWarp::
	map_script_2 VAR_TEMP_1, 0, PokemonLeague_AgathasRoom_EventScript_TurnPlayerNorth
	.2byte 0

PokemonLeague_AgathasRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

PokemonLeague_AgathasRoom_OnFrame::
	map_script_2 VAR_MAP_SCENE_POKEMON_LEAGUE, 2, PokemonLeague_AgathasRoom_EventScript_EnterRoom
	.2byte 0

PokemonLeague_AgathasRoom_EventScript_EnterRoom::
	lockall
	call PokemonLeague_EventScript_EnterRoom
	setvar VAR_MAP_SCENE_POKEMON_LEAGUE, 3
	releaseall
	end

PokemonLeague_AgathasRoom_EventScript_Agatha::
	lock
	faceplayer
	famechecker FAMECHECKER_AGATHA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	goto_if_set FLAG_DEFEATED_AGATHA, PokemonLeague_AgathasRoom_EventScript_PostBattle
	famechecker FAMECHECKER_AGATHA, 0
	famechecker FAMECHECKER_AGATHA, 4
	famechecker FAMECHECKER_OAK, 4
	call_if_unset FLAG_SYS_GAME_CLEAR, PokemonLeague_AgathasRoom_EventScript_Intro
	call_if_set FLAG_SYS_GAME_CLEAR, PokemonLeague_AgathasRoom_EventScript_RematchIntro
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	call_if_unset FLAG_IS_CHAMPION, PokemonLeague_AgathasRoom_EventScript_Battle
	call_if_set FLAG_IS_CHAMPION, PokemonLeague_AgathasRoom_EventScript_Rematch
	clearflag FLAG_TEMP_5
	goto PokemonLeague_AgathasRoom_EventScript_DefeatedAgatha
	end

PokemonLeague_AgathasRoom_EventScript_Intro::
	msgbox PokemonLeague_AgathasRoom_Text_Intro
	return

PokemonLeague_AgathasRoom_EventScript_RematchIntro::
	msgbox PokemonLeague_AgathasRoom_Text_RematchIntro
	return

PokemonLeague_AgathasRoom_EventScript_Battle::
	trainerbattle_no_intro TRAINER_ELITE_FOUR_AGATHA, PokemonLeague_AgathasRoom_Text_Defeat
	return

PokemonLeague_AgathasRoom_EventScript_Rematch::
	trainerbattle_no_intro TRAINER_ELITE_FOUR_AGATHA_2, PokemonLeague_AgathasRoom_Text_Defeat
	return

PokemonLeague_AgathasRoom_EventScript_PostBattle::
	msgbox PokemonLeague_AgathasRoom_Text_PostBattle
	release
	end

PokemonLeague_AgathasRoom_EventScript_DefeatedAgatha::
	setflag FLAG_DEFEATED_AGATHA
	call PokemonLeague_EventScript_OpenDoor
	msgbox PokemonLeague_AgathasRoom_Text_PostBattle
	release
	end

PokemonLeague_AgathasRoom_Text_Intro::
	.string "AGATHA of the ELITE FOUR.\p"
	.string "So you're the one OAK fusses over.\p"
	.string "I knew him when he was tough.\n"
	.string "When he was DANGEROUS.\p"
	.string "Now? He presses POKéMON into a\n"
	.string "book and calls it a life's work.\p"
	.string "They are not for cataloguing,\n"
	.string "child. They are for BATTLE.\p"
	.string "Come. Let an old woman remind you\n"
	.string "what that word means.{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PokemonLeague_AgathasRoom_Text_RematchIntro::
	.string "AGATHA of the ELITE FOUR.\p"
	.string "Back for more, are you, child?\p"
	.string "Good. OAK catalogues.\n"
	.string "I battle.\p"
	.string "Let's see if you still remember\n"
	.string "which one matters.{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PokemonLeague_AgathasRoom_Text_Defeat::
	.string "…Well now.\p"
	.string "There's fire in you, child.\p"
	.string "Real fire. …I like that.$"

PokemonLeague_AgathasRoom_Text_PostBattle::
	.string "You proved it the only way that\n"
	.string "counts. In the ring.\p"
	.string "…OAK was right about you.\n"
	.string "Don't tell him I said so.\p"
	.string "Off you go, child.$"

