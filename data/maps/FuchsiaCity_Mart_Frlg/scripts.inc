FuchsiaCity_Mart_Frlg_MapScripts::
	.byte 0

FuchsiaCity_Mart_EventScript_CooltrainerF::
	msgbox FuchsiaCity_Mart_Text_DidYouTryXSpeed, MSGBOX_NPC
	end

FuchsiaCity_Mart_EventScript_Gentleman::
	msgbox FuchsiaCity_Mart_Text_DontTheyHaveSafariZonePennants, MSGBOX_NPC
	end

FuchsiaCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FuchsiaCity_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
FuchsiaCity_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

FuchsiaCity_Mart_Text_DontTheyHaveSafariZonePennants::
	.string "Don't they have any pennants\n"
	.string "promoting the SAFARI ZONE?\p"
	.string "How about some paper lanterns?\n"
	.string "Aren't there even any calendars?\p"
	.string "…Forgive me. I'm the MAYOR.\n"
	.string "I fret over little things.\p"
	.string "And the big one. KOGA's stacks\n"
	.string "foul our air.\p"
	.string "KOGA's power runs our homes.\n"
	.string "Both are true.\p"
	.string "Neither side is wrong.\n"
	.string "…That is what keeps me up.$"

FuchsiaCity_Mart_Text_DidYouTryXSpeed::
	.string "Did you try X SPEED?\n"
	.string "It speeds up a POKéMON in battle.\p"
	.string "Everything's cheap in FUCHSIA.\n"
	.string "KOGA's power runs cheap.\p"
	.string "…One good thing, at least.$"

