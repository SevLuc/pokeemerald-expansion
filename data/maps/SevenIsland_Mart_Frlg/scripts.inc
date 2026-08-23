SevenIsland_Mart_Frlg_MapScripts::
	.byte 0

SevenIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SevenIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
SevenIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

SevenIsland_Mart_EventScript_Lass::
	msgbox SevenIsland_Mart_Text_MonHavePersonalitiesOfTheirOwn, MSGBOX_NPC
	end

SevenIsland_Mart_EventScript_Hiker::
	msgbox SevenIsland_Mart_Text_PreparationsCompleteForRuins, MSGBOX_NPC
	end

SevenIsland_Mart_EventScript_Fisher::
	msgbox SevenIsland_Mart_Text_NeedToFishOnSevenIsland, MSGBOX_NPC
	end

SevenIsland_Mart_Text_MonHavePersonalitiesOfTheirOwn::
	.string "The way LANCE tells it, there are\n"
	.string "two kinds of POKéMON.\p"
	.string "Dragons… and dragons that don't\n"
	.string "know it yet.\p"
	.string "…I've caught myself eyeing my own\n"
	.string "team differently since.$"

SevenIsland_Mart_Text_PreparationsCompleteForRuins::
	.string "Okay, preparations are complete\n"
	.string "for me to explore the RUINS.$"

SevenIsland_Mart_Text_NeedToFishOnSevenIsland::
	.string "I'm on a fishing tour of the\n"
	.string "SEVII ISLANDS.\p"
	.string "LANCE once called my MAGIKARP\n"
	.string "'a dragon in waiting.'\p"
	.string "…It's a GYARADOS now.\n"
	.string "I've wondered what he saw.$"

