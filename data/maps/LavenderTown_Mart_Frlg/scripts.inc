LavenderTown_Mart_Frlg_MapScripts::
	.byte 0

LavenderTown_Mart_EventScript_BaldingMan::
	msgbox LavenderTown_Mart_Text_SearchingForStatRaiseItems, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Rocker::
	msgbox LavenderTown_Mart_Text_DidYouBuyRevives, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Youngster::
	msgbox LavenderTown_Mart_Text_TrainerDuosCanChallengeYou, MSGBOX_NPC
	end

LavenderTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavenderTown_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
LavenderTown_Mart_Items::
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_NONE
	release
	end

LavenderTown_Mart_Text_SearchingForStatRaiseItems::
	.string "I helped dig ROCK TUNNEL,\n"
	.string "years back.\p"
	.string "They swore we'd have lamps by\n"
	.string "winter. We strung the wire…\p"
	.string "Then the money went quiet.\n"
	.string "It's still dark down there.\p"
	.string "I carried a candle every\n"
	.string "shift. The habit stayed.$"

LavenderTown_Mart_Text_DidYouBuyRevives::
	.string "Stock up on REVIVES while\n"
	.string "you're here.\p"
	.string "They'll bring a fainted\n"
	.string "POKéMON right back.\p"
	.string "Funny place to sell them…\n"
	.string "round here, of all towns.$"

LavenderTown_Mart_Text_TrainerDuosCanChallengeYou::
	.string "Sometimes two TRAINERS\n"
	.string "team up against you.\p"
	.string "Two POKéMON at once, side\n"
	.string "by side.\p"
	.string "You'll have to send out two\n"
	.string "of your own to answer them.$"

LavenderTown_Mart_Text_SoldNuggetFromMountainsFor5000::
	.string "この　あいだ　やまおくで\n"
	.string "きんのたまを　ひろい　ましてね！\p"
	.string "つかえない　しなもの　ですが\n"
	.string "うったら　なんと　5000¥でした$"
