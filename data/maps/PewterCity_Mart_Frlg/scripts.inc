PewterCity_Mart_Frlg_MapScripts::
	.byte 0

PewterCity_Mart_EventScript_Youngster::
	msgbox PewterCity_Mart_Text_BoughtWeirdFishFromShadyGuy, MSGBOX_NPC
	end

PewterCity_Mart_EventScript_Boy::
	msgbox PewterCity_Mart_Text_GoodThingsIfRaiseMonsDiligently, MSGBOX_NPC
	end

PewterCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart PewterCity_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
PewterCity_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

PewterCity_Mart_Text_BoughtWeirdFishFromShadyGuy::
	.string "A shady old guy sucked me into\n"
	.string "buying this weak fish for ¥500!\p"
	.string "Didn't read the fine print.\p"
	.string "…Grown-ups here go quiet about\n"
	.string "fine print. Dunno why.$"

PewterCity_Mart_Text_GoodThingsIfRaiseMonsDiligently::
	.string "Raise POKéMON right and even the\n"
	.string "weak ones will surprise you.\p"
	.string "BROCK never gives up on one.\p"
	.string "…People are a different thing,\n"
	.string "my mum says.$"

