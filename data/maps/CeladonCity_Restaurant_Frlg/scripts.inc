CeladonCity_Restaurant_Frlg_MapScripts::
	.byte 0

CeladonCity_Restaurant_EventScript_Chef::
	msgbox CeladonCity_Restaurant_Text_TakingBreakRightNow, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_Woman::
	msgbox CeladonCity_Restaurant_Text_OftenGoToDrugstore, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_COIN_CASE, CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase
	msgbox CeladonCity_Restaurant_Text_TakeThisImBusted
	checkitemspace ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Restaurant_EventScript_NoRoomForCoinCase
	giveitem_msg CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan, ITEM_COIN_CASE
	setflag FLAG_GOT_COIN_CASE
	release
	end

CeladonCity_Restaurant_EventScript_NoRoomForCoinCase::
	msgbox CeladonCity_Restaurant_Text_MakeRoomForThis
	release
	end

CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase::
	msgbox CeladonCity_Restaurant_Text_ThoughtIdWinItBack
	release
	end

CeladonCity_Restaurant_EventScript_WorkerM::
	msgbox CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner, MSGBOX_NPC
	end

CeladonCity_Restaurant_EventScript_FatMan::
	msgbox CeladonCity_Restaurant_Text_ManLostItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_Restaurant_Text_TakingBreakRightNow::
	.string "Welcome!\p"
	.string "The kitchen's resting\n"
	.string "just now.\p"
	.string "Come back hungry.$"

CeladonCity_Restaurant_Text_OftenGoToDrugstore::
	.string "My POKéMON are weak, so I often\n"
	.string "have to go to the DRUGSTORE.\p"
	.string "…Though the DRUGSTORE's best\n"
	.string "cures aren't on any shelf.\p"
	.string "ERIKA decides who gets those.$"

CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner::
	.string "Psst. There's a floor below\n"
	.string "the GAME CORNER.\p"
	.string "And no stairs meant to\n"
	.string "find it…$"

CeladonCity_Restaurant_Text_ManLostItAllAtSlots::
	.string "Munch…\p"
	.string "That fellow lost every COIN\n"
	.string "to the reels.\p"
	.string "Still ordered the big plate.$"

CeladonCity_Restaurant_Text_TakeThisImBusted::
	.string "Go on, laugh.\n"
	.string "I'm cleaned right out.\p"
	.string "No more reels. I'm going\n"
	.string "straight.\p"
	.string "Here. You take it.$"

CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan::
	.string "{PLAYER} received a COIN CASE\n"
	.string "from the man.$"

CeladonCity_Restaurant_Text_MakeRoomForThis::
	.string "Make room for this!$"

CeladonCity_Restaurant_Text_ThoughtIdWinItBack::
	.string "I always thought I was going to\n"
	.string "win it back…$"

