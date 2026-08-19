SSAnne_CaptainsOffice_Frlg_MapScripts::
	.byte 0

SSAnne_CaptainsOffice_EventScript_Captain::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HM01, SSAnne_CaptainsOffice_EventScript_AlreadyGotCut
	msgbox SSAnne_CaptainsOffice_Text_SurgeReveal
	giveitem_msg SSAnne_CaptainsOffice_Text_ObtainedHM01FromCaptain, ITEM_HM01, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox SSAnne_CaptainsOffice_Text_GoTryYourLuck
	setflag FLAG_GOT_HM01
	setvar VAR_MAP_SCENE_VERMILION_CITY, 1
	release
	end

@ Unused
SSAnne_CaptainsOffice_EventScript_NoRoomForCut::
	msgbox SSAnne_CaptainsOffice_Text_YouHaveNoRoomForThis
	closemessage
	applymovement LOCALID_SS_ANNE_CAPTAIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SSAnne_CaptainsOffice_EventScript_AlreadyGotCut::
	msgbox SSAnne_CaptainsOffice_Text_ReTalkLore
	msgbox SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon
	release
	end

SSAnne_CaptainsOffice_EventScript_TrashCan::
	msgbox SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_EventScript_Book::
	msgbox SSAnne_CaptainsOffice_Text_HowToConquerSeasickness, MSGBOX_SIGN
	end

SSAnne_CaptainsOffice_Text_SurgeReveal::
	.string "CAPTAIN: Challenger!\n"
	.string "You made it through.\p"
	.string "Many want to face the LT.\p"
	.string "His locks and trials turn away\n"
	.string "the unworthy.\p"
	.string "You cleared the first of them.\p"
	.string "You see a free port today.\n"
	.string "Once, it was anything but.\p"
	.string "TEAM ROCKET ran these docks.\n"
	.string "Fear ran the streets.\p"
	.string "From the slums came a boy.\n"
	.string "No name. No rank. Only nerve.\p"
	.string "He signed on. Just a private,\n"
	.string "hauling electric cargo.\p"
	.string "He watched, waited, and rose\n"
	.string "to LIEUTENANT of the ship.\p"
	.string "Then, one night, he freed them.\n"
	.string "The electric POKéMON in the hold.\p"
	.string "Together they struck,\n"
	.string "LIGHTNING fast.\p"
	.string "By dawn, ROCKET was driven\n"
	.string "from VERMILION.\p"
	.string "The city could breathe again.\p"
	.string "He left the people to rule\n"
	.string "themselves.\p"
	.string "He stayed only to guard them.\p"
	.string "That is why he holds the gym.\n"
	.string "Not a king. A shield.$"

SSAnne_CaptainsOffice_Text_ObtainedHM01FromCaptain::
	.string "{PLAYER} obtained HM01\n"
	.string "from the CAPTAIN!$"

SSAnne_CaptainsOffice_Text_GoTryYourLuck::
	.string "Now that you've seen where it\n"
	.string "all began, go and face the LT.\p"
	.string "Use CUT to clear the tree\n"
	.string "at his gym.\p"
	.string "And pay the man your respects.$"

SSAnne_CaptainsOffice_Text_ReTalkLore::
	.string "CAPTAIN: I owe that man a lot.\p"
	.string "…We all do.$"

SSAnne_CaptainsOffice_Text_SSAnneWillSetSailSoon::
	.string "The S.S. ANNE will set sail soon.\p"
	.string "Farewell, until we return to\n"
	.string "VERMILION CITY!$"

SSAnne_CaptainsOffice_Text_YouHaveNoRoomForThis::
	.string "Oh, no!\n"
	.string "You have no room for this!$"

SSAnne_CaptainsOffice_Text_YuckShouldntHaveLooked::
	.string "Yuck!\n"
	.string "Shouldn't have looked!$"

SSAnne_CaptainsOffice_Text_HowToConquerSeasickness::
	.string "How to Conquer Seasickness…\n"
	.string "The CAPTAIN's reading this!$"
