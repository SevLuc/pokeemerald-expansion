PokemonTower_2F_Frlg_MapScripts::
	.byte 0

PokemonTower_2F_EventScript_Channeler::
	msgbox PokemonTower_2F_Text_SilphScopeCouldUnmaskGhosts, MSGBOX_NPC
	end

PokemonTower_2F_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 0
	goto PokemonTower_2F_EventScript_Rival
	end

PokemonTower_2F_EventScript_RivalTriggerDown::
	lockall
	setvar VAR_TEMP_1, 1
	goto PokemonTower_2F_EventScript_Rival
	end

PokemonTower_2F_EventScript_Rival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	call_if_eq VAR_TEMP_1, 0, PokemonTower_2F_EventScript_RivalFacePlayerRight
	call_if_eq VAR_TEMP_1, 1, PokemonTower_2F_EventScript_RivalFacePlayerDown
	applymovement LOCALID_POKEMON_TOWER_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_POKEMON_TOWER_RIVAL, Common_Movement_Delay48
	waitmovement 0
	setvar VAR_LAST_TALKED, LOCALID_POKEMON_TOWER_RIVAL
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_TWITCH, PokemonTower_2F_EventScript_RivalTwitch
	msgbox PokemonTower_2F_Text_RivalIntro
	call_if_eq VAR_STARTER_MON, 2, PokemonTower_2F_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, PokemonTower_2F_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, PokemonTower_2F_EventScript_RivalCharmander
	msgbox PokemonTower_2F_Text_RivalPostBattle
PokemonTower_2F_EventScript_RivalDepart::
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, PokemonTower_2F_EventScript_RivalExitRight
	call_if_eq VAR_TEMP_1, 1, PokemonTower_2F_EventScript_RivalExitDown
	playse SE_EXIT
	delay 25
	fadedefaultbgm
	removeobject LOCALID_POKEMON_TOWER_RIVAL
	setvar VAR_MAP_SCENE_POKEMON_TOWER_2F, 1
	setflag FLAG_DEFEATED_POKEMON_TOWER_RIVAL
	releaseall
	end

PokemonTower_2F_EventScript_RivalFacePlayerRight::
	applymovement LOCALID_POKEMON_TOWER_RIVAL, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

PokemonTower_2F_EventScript_RivalFacePlayerDown::
	applymovement LOCALID_POKEMON_TOWER_RIVAL, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

PokemonTower_2F_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE, PokemonTower_2F_Text_RivalDefeat
	return

PokemonTower_2F_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR, PokemonTower_2F_Text_RivalDefeat
	return

PokemonTower_2F_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER, PokemonTower_2F_Text_RivalDefeat
	return

PokemonTower_2F_EventScript_RivalTwitch::
	msgbox PokemonTower_2F_Text_TwitchRivalIntro
	trainerbattle_no_intro TRAINER_RIVAL_TWITCH_POKEMON_TOWER, PokemonTower_2F_Text_TwitchRivalDefeat
	msgbox PokemonTower_2F_Text_TwitchRivalPostBattle
	goto PokemonTower_2F_EventScript_RivalDepart

PokemonTower_2F_EventScript_RivalExitRight::
	applymovement LOCALID_POKEMON_TOWER_RIVAL, PokemonTower_2F_Movement_RivalExitRight
	waitmovement 0
	return

PokemonTower_2F_EventScript_RivalExitDown::
	applymovement LOCALID_POKEMON_TOWER_RIVAL, PokemonTower_2F_Movement_RivalExitDown
	waitmovement 0
	return

PokemonTower_2F_Movement_RivalExitRight::
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PokemonTower_2F_Movement_RivalExitDown::
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PokemonTower_2F_Text_RivalIntro::
	.string "{PLAYER}! Yo where's the\n"
	.string "TEA bro?\p"
	.string "How do I get the TEA?\p"
	.string "you got TEA?$"

PokemonTower_2F_Text_RivalDefeat::
	.string "If I was tea…\n"
	.string "where would I be?$"

PokemonTower_2F_Text_RivalPostBattle::
	.string "How's your POKéDEX coming?\n"
	.string "I just caught a CUBONE!\p"
	.string "I can't find the bigger MAROWAK.\n"
	.string "Where could they be?\p"
	.string "I bet there aren't any left!\p"
	.string "Well, I better get going.\n"
	.string "I've got a lot to accomplish,\l"
	.string "unlike you.\p"
	.string "Smell ya later!$"

PokemonTower_2F_Text_TwitchRivalIntro::
	.string "is your mon dead? for real?\n"
	.string "F IN CHAT.\p"
	.string "this whole tower is THE\n"
	.string "GRAVEYARD. we know it well.\p"
	.string "our starter is in a box up there.\n"
	.string "ABBY is in a box.\p"
	.string "it is not dead, it is just boxed.\n"
	.string "forever.\p"
	.string "anyway. throw hands in a\n"
	.string "graveyard? sure.$"

PokemonTower_2F_Text_TwitchRivalDefeat::
	.string "NOT THE ACE. not the ace…\p"
	.string "that is the run. pour one out.\p"
	.string "F. F. one more F.\n"
	.string "thank you, chat.$"

PokemonTower_2F_Text_TwitchRivalPostBattle::
	.string "pants stay brown.\n"
	.string "we stayed composed.\p"
	.string "we did NOT wipe. mostly.\n"
	.string "we go next.$"

PokemonTower_2F_Text_SilphScopeCouldUnmaskGhosts::
	.string "Even we could not identify the\n"
	.string "wayward ghosts.\p"
	.string "A SILPH SCOPE might be able to\n"
	.string "unmask them.$"

