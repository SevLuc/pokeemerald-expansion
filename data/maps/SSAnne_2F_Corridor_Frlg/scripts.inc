SSAnne_2F_Corridor_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Corridor_EventScript_Ann::
	trainerbattle_single TRAINER_LASS_ANN, SSAnne_2F_Corridor_Text_AnnIntro, SSAnne_2F_Corridor_Text_AnnDefeat
	msgbox SSAnne_2F_Corridor_Text_AnnPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Corridor_EventScript_Dale::
	trainerbattle_single TRAINER_FISHERMAN_DALE, SSAnne_2F_Corridor_Text_DaleIntro, SSAnne_2F_Corridor_Text_DaleDefeat
	msgbox SSAnne_2F_Corridor_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Corridor_EventScript_Arthur::
	trainerbattle_single TRAINER_GENTLEMAN_ARTHUR, SSAnne_2F_Corridor_Text_ArthurIntro, SSAnne_2F_Corridor_Text_ArthurDefeat
	msgbox SSAnne_2F_Corridor_Text_ArthurPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Corridor_EventScript_Phillip::
	trainerbattle_single TRAINER_SAILOR_PHILLIP, SSAnne_2F_Corridor_Text_PhillipIntro, SSAnne_2F_Corridor_Text_PhillipDefeat
	msgbox SSAnne_2F_Corridor_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Corridor_Text_AnnIntro::
	.string "I collected these POKéMON\n"
	.string "from all around the world!$"

SSAnne_2F_Corridor_Text_AnnDefeat::
	.string "Oh, no!\n"
	.string "I went around the world for these!$"

SSAnne_2F_Corridor_Text_AnnPostBattle::
	.string "You hurt my poor POKéMON!\p"
	.string "I demand that you heal them at a\n"
	.string "POKéMON CENTER!$"

SSAnne_2F_Corridor_Text_DaleIntro::
	.string "Check out what I fished up!$"

SSAnne_2F_Corridor_Text_DaleDefeat::
	.string "I'm all out!$"

SSAnne_2F_Corridor_Text_DalePostBattle::
	.string "Party?\p"
	.string "The cruise ship's party should be\n"
	.string "over by now.$"

SSAnne_2F_Corridor_Text_ArthurIntro::
	.string "You insolent pup!\n"
	.string "How dare you barge in!$"

SSAnne_2F_Corridor_Text_ArthurDefeat::
	.string "Humph! You rude child!\n"
	.string "You have no sense of courtesy!$"

SSAnne_2F_Corridor_Text_ArthurPostBattle::
	.string "I wish to be left alone!\n"
	.string "Get out!$"

SSAnne_2F_Corridor_Text_PhillipIntro::
	.string "Matey, you're walking the plank if\n"
	.string "you lose!$"

SSAnne_2F_Corridor_Text_PhillipDefeat::
	.string "Argh!\n"
	.string "Beaten by a kid!$"

SSAnne_2F_Corridor_Text_PhillipPostBattle::
	.string "When we're out at sea, jellyfish\n"
	.string "POKéMON sometimes drift by.$"

SSAnne_2F_Corridor_EventScript_RivalTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto SSAnne_2F_Corridor_EventScript_RivalTrigger
	end

SSAnne_2F_Corridor_EventScript_RivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	goto SSAnne_2F_Corridor_EventScript_RivalTrigger
	end

SSAnne_2F_Corridor_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	goto SSAnne_2F_Corridor_EventScript_RivalTrigger
	end

SSAnne_2F_Corridor_EventScript_RivalTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	playse SE_EXIT
	delay 5
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_SS_ANNE_RIVAL
	delay 10
	applymovement LOCALID_SS_ANNE_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 20
	call_if_eq VAR_TEMP_1, 0, SSAnne_2F_Corridor_EventScript_RivalApproachLeft
	call_if_eq VAR_TEMP_1, 1, SSAnne_2F_Corridor_EventScript_RivalApproachMid
	call_if_eq VAR_TEMP_1, 2, SSAnne_2F_Corridor_EventScript_RivalApproachRight
	setvar VAR_LAST_TALKED, LOCALID_SS_ANNE_RIVAL
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_TWITCH, SSAnne_2F_Corridor_EventScript_RivalTwitch
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_LOCKE, SSAnne_2F_Corridor_EventScript_RivalLocke
	msgbox SSAnne_2F_Corridor_Text_RivalIntro
	call_if_eq VAR_STARTER_MON, 2, SSAnne_2F_Corridor_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, SSAnne_2F_Corridor_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, SSAnne_2F_Corridor_EventScript_RivalCharmander
	msgbox SSAnne_2F_Corridor_Text_RivalPostBattle
SSAnne_2F_Corridor_EventScript_RivalDepart::
	closemessage
	delay 10
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, SSAnne_2F_Corridor_EventScript_RivalExitLeft
	call_if_eq VAR_TEMP_1, 1, SSAnne_2F_Corridor_EventScript_RivalExitMid
	call_if_eq VAR_TEMP_1, 2, SSAnne_2F_Corridor_EventScript_RivalExitRight
	fadedefaultbgm
	removeobject LOCALID_SS_ANNE_RIVAL
	setvar VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR, 1
	releaseall
	end

SSAnne_2F_Corridor_EventScript_RivalApproachLeft::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalApproachLeft
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalApproachMid::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalApproachMid
	applymovement LOCALID_PLAYER, SSAnne_2F_Corridor_Movement_PlayerFaceRivalMid
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalApproachRight::
	applymovement LOCALID_PLAYER, SSAnne_2F_Corridor_Movement_PlayerFaceRivalRight
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalApproachRight
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_SS_ANNE_SQUIRTLE, SSAnne_2F_Corridor_Text_RivalDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_SS_ANNE_BULBASAUR, SSAnne_2F_Corridor_Text_RivalDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_SS_ANNE_CHARMANDER, SSAnne_2F_Corridor_Text_RivalDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalTwitch::
	msgbox SSAnne_2F_Corridor_Text_TwitchRivalIntro
	trainerbattle_no_intro TRAINER_RIVAL_TWITCH_SS_ANNE, SSAnne_2F_Corridor_Text_TwitchRivalDefeat
	msgbox SSAnne_2F_Corridor_Text_TwitchRivalPostBattle
	goto SSAnne_2F_Corridor_EventScript_RivalDepart

@ Locke keeps the vanilla per-starter split (own intro/defeat/post text).
SSAnne_2F_Corridor_EventScript_RivalLocke::
	msgbox SSAnne_2F_Corridor_Text_LockeRivalIntro
	call_if_eq VAR_STARTER_MON, 2, SSAnne_2F_Corridor_EventScript_RivalLockeSquirtle
	call_if_eq VAR_STARTER_MON, 1, SSAnne_2F_Corridor_EventScript_RivalLockeBulbasaur
	call_if_eq VAR_STARTER_MON, 0, SSAnne_2F_Corridor_EventScript_RivalLockeCharmander
	msgbox SSAnne_2F_Corridor_Text_LockeRivalPostBattle
	goto SSAnne_2F_Corridor_EventScript_RivalDepart

SSAnne_2F_Corridor_EventScript_RivalLockeSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_SS_ANNE_SQUIRTLE, SSAnne_2F_Corridor_Text_LockeRivalDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalLockeBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_SS_ANNE_BULBASAUR, SSAnne_2F_Corridor_Text_LockeRivalDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalLockeCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_SS_ANNE_CHARMANDER, SSAnne_2F_Corridor_Text_LockeRivalDefeat
	return

SSAnne_2F_Corridor_EventScript_RivalExitLeft::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalExitLeft
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalExitMid::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalExitMid
	waitmovement 0
	return

SSAnne_2F_Corridor_EventScript_RivalExitRight::
	applymovement LOCALID_SS_ANNE_RIVAL, SSAnne_2F_Corridor_Movement_RivalExitRight
	waitmovement 0
	return

SSAnne_2F_Corridor_Movement_PlayerFaceRivalRight::
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SSAnne_2F_Corridor_Movement_PlayerFaceRivalMid::
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SSAnne_2F_Corridor_Movement_RivalApproachLeft::
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_Movement_RivalApproachMid::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

SSAnne_2F_Corridor_Movement_RivalApproachRight::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	delay_4
	step_end

SSAnne_2F_Corridor_Movement_RivalExitLeft::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_Movement_RivalExitMid::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_Movement_RivalExitRight::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_2F_Corridor_EventScript_Sailor::
	msgbox SSAnne_2F_Corridor_Text_ThisShipIsLuxuryLiner, MSGBOX_NPC
	end

SSAnne_2F_Corridor_Text_ThisShipIsLuxuryLiner::
	.string "This ship's a luxury liner for\n"
	.string "TRAINERS the world over!\p"
	.string "Cleanest deck in the fleet.\n"
	.string "Wasn't, once. Someone saw to that.$"

SSAnne_2F_Corridor_Text_RivalIntro::
	.string "Yooo whats good my guy?\p"
	.string "You got past the gauntlet\n"
	.string "too??\p"
	.string "You are him bro!\p"
	.string "Thats some good\n"
	.string "calculations with the\l"
	.string "dome piece!\p"
	.string "… a fight?\p"
	.string "alright betski,\n"
	.string "I accidentally edged my\l"
	.string "pokemon,\p"
	.string "now I got to use the\n"
	.string "homeless version of my\l"
	.string "team.$"

SSAnne_2F_Corridor_Text_RivalDefeat::
	.string "W fight$"

SSAnne_2F_Corridor_Text_RivalVictory::
	.string "{PLAYER}..！\n"
	.string "ふなよい　してるのか！\p"
	.string "もっと　からだ\n"
	.string "きたえた　ほうが　いいぜ！$"

SSAnne_2F_Corridor_Text_RivalPostBattle::
	.string "Oh yo, theres a CUT master\n"
	.string "on this boat, so CUT in.\p"
	.string "Do I actually need to\n"
	.string "teach a guy CUT?\p"
	.string "Like come on bro.\p"
	.string "Alright we are outta here!$"

SSAnne_2F_Corridor_Text_TwitchRivalIntro::
	.string "chat we EVOLVED and we look\n"
	.string "GREAT. respect the art.\p"
	.string "you got past the gauntlet too??\n"
	.string "DOESHEKNOW. he does not know.\p"
	.string "fancy boat, fancy us.\n"
	.string "so this is a fight. bet.$"

SSAnne_2F_Corridor_Text_TwitchRivalDefeat::
	.string "HAXED. that was a crit.\p"
	.string "it was a RANGE and we clicked\n"
	.string "it anyway.\p"
	.string "we did the math and the math\n"
	.string "lied to us.$"

SSAnne_2F_Corridor_Text_TwitchRivalPostBattle::
	.string "theres a CUT master on this\n"
	.string "boat, go get CUT.\p"
	.string "do we actually need to teach\n"
	.string "a guy CUT? whatever.\p"
	.string "we are outta here. GG.$"

SSAnne_2F_Corridor_Text_LockeRivalIntro::
	.string "Luxury episode, chat!\n"
	.string "Big boat, big run.\p"
	.string "Still deathless. That's\n"
	.string "the brand.\p"
	.string "And you? You belong\n"
	.string "on this deck. Roll it.$"

SSAnne_2F_Corridor_Text_LockeRivalDefeat::
	.string "Losing in style!\n"
	.string "Frame it nice.\p"
	.string "That was gorgeous,\n"
	.string "challenger. Thank you.\p"
	.string "The run goes on. It\n"
	.string "always does.\p"
	.string "And I'm so glad you're\n"
	.string "on it. Really. I am.$"

SSAnne_2F_Corridor_Text_LockeRivalPostBattle::
	.string "There's a CUT master\n"
	.string "aboard. Go get CUT.\p"
	.string "Great for the show.\p"
	.string "Thank you for playing,\n"
	.string "{PLAYER}. Roll it.$"

