LavenderTown_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavenderTown_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_LAVENDER_TOWN
	end

LavenderTown_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

LavenderTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavenderTown_PokemonCenter_1F_Text_RocketsDoAnythingForMoney, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_EventScript_Lass::
	msgbox LavenderTown_PokemonCenter_1F_Text_CubonesMotherKilledByRockets, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavenderTown_PokemonCenter_1F_Text_PeoplePayForCuboneSkulls, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_Text_RocketsDoAnythingForMoney::
	.string "You know AGATHA of the ELITE\n"
	.string "FOUR? The GHOST trainer?\p"
	.string "She trained here as a girl, among\n"
	.string "the TOWER's spirits.\p"
	.string "Fierce even then. …Back when a\n"
	.string "friend of hers chose books over\l"
	.string "battle.$"

LavenderTown_PokemonCenter_1F_Text_CubonesMotherKilledByRockets::
	.string "I saw it happen.\p"
	.string "The mother CUBONE, running\n"
	.string "from those ROCKETS…\p"
	.string "She didn't get far.\p"
	.string "I still hear it, when the\n"
	.string "night goes quiet.$"

LavenderTown_PokemonCenter_1F_Text_PeoplePayForCuboneSkulls::
	.string "My grandpa tells this old\n"
	.string "story.\p"
	.string "A TRAINER who walked all\n"
	.string "KANTO with an empty belt.\p"
	.string "Caught nothing. The wild ones\n"
	.string "just followed him.\p"
	.string "I called it a fairy tale…\p"
	.string "Then one on the path wouldn't\n"
	.string "run from me. Now I wonder.$"

