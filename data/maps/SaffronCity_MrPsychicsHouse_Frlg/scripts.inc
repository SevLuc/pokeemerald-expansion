SaffronCity_MrPsychicsHouse_Frlg_MapScripts::
	.byte 0

SaffronCity_MrPsychicsHouse_EventScript_MrPsychic::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM29_FROM_MR_PSYCHIC, SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29
	msgbox SaffronCity_MrPsychicsHouse_Text_YouWantedThis
	checkitemspace ITEM_TM29
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_MrPsychicsHouse_EventScript_NoRoomForTM29
	giveitem_msg SaffronCity_MrPsychicsHouse_Text_ReceivedTM29FromMrPsychic, ITEM_TM29
	msgbox SaffronCity_MrPsychicsHouse_Text_ExplainTM29
	setflag FLAG_GOT_TM29_FROM_MR_PSYCHIC
	goto SaffronCity_MrPsychicsHouse_EventScript_SabrinaTalk
	end

SaffronCity_MrPsychicsHouse_EventScript_NoRoomForTM29::
	msgbox SaffronCity_MrPsychicsHouse_Text_YouveNoRoom
	release
	end

SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29::
	goto SaffronCity_MrPsychicsHouse_EventScript_SabrinaTalk
	end

SaffronCity_MrPsychicsHouse_EventScript_SabrinaTalk::
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_MrPsychicsHouse_EventScript_SabrinaFreed
	msgbox SaffronCity_MrPsychicsHouse_Text_SabrinaWarning
	release
	end

SaffronCity_MrPsychicsHouse_EventScript_SabrinaFreed::
	msgbox SaffronCity_MrPsychicsHouse_Text_SabrinaFreed
	release
	end

SaffronCity_MrPsychicsHouse_Text_YouWantedThis::
	.string "…Wait! Don't say a word!\p"
	.string "You wanted this!$"

SaffronCity_MrPsychicsHouse_Text_ReceivedTM29FromMrPsychic::
	.string "{PLAYER} received TM29\n"
	.string "from MR. PSYCHIC.$"

SaffronCity_MrPsychicsHouse_Text_ExplainTM29::
	.string "You already know, don't you?\n"
	.string "TM29 is PSYCHIC.\p"
	.string "It's an attack that may also lower\n"
	.string "the target's special stats.$"

SaffronCity_MrPsychicsHouse_Text_YouveNoRoom::
	.string "Where do you plan to put this?\n"
	.string "You've no room.$"

SaffronCity_MrPsychicsHouse_Text_SabrinaWarning::
	.string "You feel it too, don't you.\n"
	.string "The wrongness in the air.\p"
	.string "I taught SABRINA, once.\n"
	.string "A sunny child. Sunlight itself.\p"
	.string "But her gift grew past her.\n"
	.string "It began to reach. To take.\p"
	.string "The vanished are not lost. They\n"
	.string "sleep within her. And her dolls.\p"
	.string "Her heart went cold to cage that\n"
	.string "power. Only warmth can thaw it.\p"
	.string "Make her FEEL something, child.\n"
	.string "Surprise her. It is the only way.$"

SaffronCity_MrPsychicsHouse_Text_SabrinaFreed::
	.string "You did it. You made her LAUGH.\p"
	.string "I felt it across the whole city,\n"
	.string "like a window thrown wide.\p"
	.string "The cold let go. The vanished woke.\n"
	.string "The sunny girl is in there still.\p"
	.string "You gave SAFFRON back its daughter.\n"
	.string "…An old teacher thanks you.$"

