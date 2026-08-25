PokemonTower_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonTower_1F_OnTransition
	.byte 0

PokemonTower_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_POKEMON_TOWER_1F
	end

PokemonTower_1F_EventScript_Channeler::
	msgbox PokemonTower_1F_Text_SenseSpiritsUpToMischief, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_Woman1::
	msgbox PokemonTower_1F_Text_GrowlitheWhyDidYouDie, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_BaldingMan::
	msgbox PokemonTower_1F_Text_CameToPrayForDepartedClefairy, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_Woman2::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PokemonTower_1F_EventScript_Woman2MalePlayer
	msgbox PokemonTower_1F_Text_ComeToPayRespectsGirl
	release
	end

PokemonTower_1F_EventScript_Woman2MalePlayer::
	msgbox PokemonTower_1F_Text_ComeToPayRespectsSon
	release
	end

PokemonTower_1F_EventScript_WorkerF::
	msgbox PokemonTower_1F_Text_ErectedInMemoryOfDeadMons, MSGBOX_NPC
	end

PokemonTower_1F_Text_ErectedInMemoryOfDeadMons::
	.string "POKéMON TOWER stands for\n"
	.string "the ones we've lost.\p"
	.string "Every grave here was\n"
	.string "someone's dearest friend.\p"
	.string "Walk softly. They can hear\n"
	.string "you.$"

PokemonTower_1F_Text_ComeToPayRespectsSon::
	.string "Did you come to pay respects?\p"
	.string "Bless your POKéMON-loving heart,\n"
	.string "son.$"

PokemonTower_1F_Text_ComeToPayRespectsGirl::
	.string "Have you come to pay your\n"
	.string "respects?\p"
	.string "Bless you, child.\p"
	.string "Few young ones stop here.\p"
	.string "The POKéMON rest easier for\n"
	.string "a kind heart.$"

PokemonTower_1F_Text_CameToPrayForDepartedClefairy::
	.string "I came to sit with my\n"
	.string "CLEFAIRY.\p"
	.string "We watched a good many moons\n"
	.string "come full, that one and I.\p"
	.string "Now I watch them alone.\n"
	.string "Sniff…$"

PokemonTower_1F_Text_GrowlitheWhyDidYouDie::
	.string "My GROWLITHE…\p"
	.string "You kept me warm through\n"
	.string "every winter I had.\p"
	.string "Why did you have to go\n"
	.string "first? …Why?$"

PokemonTower_1F_Text_SenseSpiritsUpToMischief::
	.string "I am a CHANNELER.\p"
	.string "The spirits here are\n"
	.string "restless. Something stirs them.\p"
	.string "High in the TOWER… it will\n"
	.string "not let them sleep.$"

