SSAnne_Kitchen_Frlg_MapScripts::
	.byte 0

SSAnne_Kitchen_EventScript_Chef1::
	msgbox SSAnne_Kitchen_Text_BusyOutOfTheWay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef2::
	msgbox SSAnne_Kitchen_Text_SawOddBerryInTrash, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef3::
	msgbox SSAnne_Kitchen_Text_SoBusyImDizzy, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef4::
	lock
	faceplayer
	msgbox SSAnne_Kitchen_Text_IAmLeChefMainCourseIs
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, SSAnne_Kitchen_EventScript_SalmonDuSalad
	call_if_eq VAR_0x8008, 1, SSAnne_Kitchen_EventScript_EelsAuBarbecue
	call_if_eq VAR_0x8008, 2, SSAnne_Kitchen_EventScript_PrimeBeefsteak
	release
	end

SSAnne_Kitchen_EventScript_SalmonDuSalad::
	msgbox SSAnne_Kitchen_Text_SalmonDuSalad
	return

SSAnne_Kitchen_EventScript_EelsAuBarbecue::
	msgbox SSAnne_Kitchen_Text_EelsAuBarbecue
	return

SSAnne_Kitchen_EventScript_PrimeBeefsteak::
	msgbox SSAnne_Kitchen_Text_PrimeBeefsteak
	return

SSAnne_Kitchen_EventScript_Chef5::
	msgbox SSAnne_Kitchen_Text_PeelSpudsEveryDay, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef6::
	msgbox SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton, MSGBOX_NPC
	end

SSAnne_Kitchen_EventScript_Chef7::
	msgbox SSAnne_Kitchen_Text_OnlyGetToPeelOnions, MSGBOX_NPC
	end

SSAnne_Kitchen_Text_BusyOutOfTheWay::
	.string "Coming through! Hot pans!\p"
	.string "We plate two hundred covers\n"
	.string "tonight. Mind your elbows.$"

SSAnne_Kitchen_Text_SawOddBerryInTrash::
	.string "Found a strange BERRY in the bin\n"
	.string "this morning.\p"
	.string "Tossed by mistake, I'd wager. A\n"
	.string "good cook wastes nothing.$"

SSAnne_Kitchen_Text_SoBusyImDizzy::
	.string "Six orders up and my head's\n"
	.string "spinning.\p"
	.string "Give a working cook some room,\n"
	.string "would you?$"

SSAnne_Kitchen_Text_PeelSpudsEveryDay::
	.string "Hum-de-hum… peeling spuds\n"
	.string "again.\p"
	.string "Honest work. The soup doesn't\n"
	.string "care whose hands made it.$"

SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton::
	.string "You ever cook for a SNORLAX?\p"
	.string "That one could clear my whole\n"
	.string "larder and still ask for pudding.$"

SSAnne_Kitchen_Text_OnlyGetToPeelOnions::
	.string "Sniff… five years trained, and\n"
	.string "still only the onions…\p"
	.string "It's the onions making me cry.\n"
	.string "…It's the onions. Truly.$"

SSAnne_Kitchen_Text_IAmLeChefMainCourseIs::
	.string "Ahem. Behold. I am LE CHEF.\p"
	.string "Tonight's masterpiece, my life's\n"
	.string "great work, it is…\p"
	.string "…a potato. A very fine potato.$"

SSAnne_Kitchen_Text_SalmonDuSalad::
	.string "Salmon du Salad!\p"
	.string "Les guests may gripe it's fish\n"
	.string "again, however!$"

SSAnne_Kitchen_Text_EelsAuBarbecue::
	.string "Eels au Barbecue!\p"
	.string "Les guests will mutiny, I fear.$"

SSAnne_Kitchen_Text_PrimeBeefsteak::
	.string "Prime Beefsteak!\p"
	.string "But, have I enough fillets du\n"
	.string "beef?$"

