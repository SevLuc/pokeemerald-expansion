Route2_ViridianForest_SouthEntrance_Frlg_MapScripts::
	.byte 0

Route2_ViridianForest_SouthEntrance_EventScript_Woman1::
	msgbox Route2_ViridianForest_SouthEntrance_Text_ForestIsMaze, MSGBOX_NPC
	end

Route2_ViridianForest_SouthEntrance_EventScript_Woman2::
	msgbox Route2_ViridianForest_SouthEntrance_Text_RattataHasWickedBite, MSGBOX_NPC
	end

Route2_ViridianForest_SouthEntrance_Text_ForestIsMaze::
	.string "Bound for VIRIDIAN FOREST?\n"
	.string "It's a green maze in there.\l"
	.string "Mind you don't lose the path.$"

Route2_ViridianForest_SouthEntrance_Text_RattataHasWickedBite::
	.string "RATTATA looks like nothing much.\n"
	.string "That bite says otherwise.\p"
	.string "Caught yourself one yet?$"

