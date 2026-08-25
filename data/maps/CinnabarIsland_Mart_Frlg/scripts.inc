CinnabarIsland_Mart_Frlg_MapScripts::
	.byte 0

CinnabarIsland_Mart_EventScript_Woman::
	msgbox CinnabarIsland_Mart_Text_DontTheyHaveXAttack, MSGBOX_NPC
	end

CinnabarIsland_Mart_EventScript_Scientist::
	msgbox CinnabarIsland_Mart_Text_ExtraItemsNeverHurt, MSGBOX_NPC
	end

CinnabarIsland_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CinnabarIsland_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
CinnabarIsland_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

CinnabarIsland_Mart_Text_DontTheyHaveXAttack::
	.string "You get used to the heat here\n"
	.string "soon enough.\p"
	.string "Me, I never leave this MART\n"
	.string "without a full bag.\p"
	.string "…You never know, on an island\n"
	.string "like this one.$"

CinnabarIsland_Mart_Text_ExtraItemsNeverHurt::
	.string "I came to study the volcano.\p"
	.string "Funny thing, though…\p"
	.string "The real work on this island\n"
	.string "ended long ago.\p"
	.string "In a fire, they say. Before\n"
	.string "the LAB. Before any of us.$"

