SSAnne_1F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room2_EventScript_Woman::
	msgbox SSAnne_1F_Room2_Text_CruisingAroundWorld, MSGBOX_NPC
	end

SSAnne_1F_Room2_EventScript_Tyler::
	trainerbattle_single TRAINER_YOUNGSTER_TYLER, SSAnne_1F_Room2_Text_TylerIntro, SSAnne_1F_Room2_Text_TylerDefeat
	msgbox SSAnne_1F_Room2_Text_TylerPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_1F_Room2_Text_TylerIntro::
	.string "I love POKéMON!\n"
	.string "Do you?$"

SSAnne_1F_Room2_Text_TylerDefeat::
	.string "Wow! \n"
	.string "You're great!$"

SSAnne_1F_Room2_Text_TylerPostBattle::
	.string "Listen, listen!\n"
	.string "Let me be your friend, okay?\p"
	.string "Then we can trade POKéMON and\n"
	.string "do stuff.$"

SSAnne_1F_Room2_Text_CruisingAroundWorld::
	.string "One cruise a year,\n"
	.string "the children and I.\p"
	.string "They count the ports off\n"
	.string "on their fingers…$"

