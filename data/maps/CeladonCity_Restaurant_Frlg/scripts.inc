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
	.string "Ah, welcome!\p"
	.string "Forgive us. The kitchen's\n"
	.string "resting just now.\p"
	.string "Come back with an appetite.$"

CeladonCity_Restaurant_Text_OftenGoToDrugstore::
	.string "My POKéMON are weak, so I often\n"
	.string "have to go to the DRUGSTORE.\p"
	.string "…Though the DRUGSTORE's best\n"
	.string "cures aren't on any shelf.\p"
	.string "ERIKA decides who gets those.$"

CeladonCity_Restaurant_Text_PsstBasementUnderGameCorner::
	.string "Psst. Word is there's a\n"
	.string "floor below the GAME CORNER.\p"
	.string "And no stairs down to it\n"
	.string "that you're meant to find.\p"
	.string "…I didn't say that.$"

CeladonCity_Restaurant_Text_ManLostItAllAtSlots::
	.string "Munch…\p"
	.string "See the fellow at that table?\p"
	.string "Lost every COIN to the reels.\n"
	.string "Still ordered the big plate.\p"
	.string "…Some appetites you can't\n"
	.string "gamble away.$"

CeladonCity_Restaurant_Text_TakeThisImBusted::
	.string "Go on, laugh.\n"
	.string "I'm cleaned right out.\p"
	.string "No more reels for me.\n"
	.string "I'm walking a straight line now.\p"
	.string "Here. You take it.\n"
	.string "I won't be needing it.$"

CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan::
	.string "{PLAYER} received a COIN CASE\n"
	.string "from the man.$"

CeladonCity_Restaurant_Text_MakeRoomForThis::
	.string "Make room for this!$"

CeladonCity_Restaurant_Text_ThoughtIdWinItBack::
	.string "I always thought I was going to\n"
	.string "win it back…$"

