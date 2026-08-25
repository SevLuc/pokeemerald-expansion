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
	.string "Coming through, hot pans!\p"
	.string "Two hundred covers tonight.\n"
	.string "Mind your elbows…$"

SSAnne_Kitchen_Text_SawOddBerryInTrash::
	.string "Found a strange BERRY\n"
	.string "in the bin.\p"
	.string "Tossed by mistake,\n"
	.string "I'd wager…$"

SSAnne_Kitchen_Text_SoBusyImDizzy::
	.string "Six orders up, head\n"
	.string "spinning.\p"
	.string "Give a working cook\n"
	.string "some room…$"

SSAnne_Kitchen_Text_PeelSpudsEveryDay::
	.string "Hum-de-hum… spuds\n"
	.string "again.\p"
	.string "Same today as yesterday…$"

SSAnne_Kitchen_Text_HearAboutSnorlaxItsAGlutton::
	.string "You ever cook for a\n"
	.string "SNORLAX?\p"
	.string "Clears my whole larder,\n"
	.string "then eyes the pudding…$"

SSAnne_Kitchen_Text_OnlyGetToPeelOnions::
	.string "Sniff… five years trained,\n"
	.string "still only the onions…\p"
	.string "It's the onions making\n"
	.string "me cry.\p"
	.string "…It's the onions.$"

SSAnne_Kitchen_Text_IAmLeChefMainCourseIs::
	.string "Ahem. Behold.\n"
	.string "I am LE CHEF.\p"
	.string "Tonight's masterpiece,\n"
	.string "my life's work…\p"
	.string "…a potato.\n"
	.string "A very fine potato.$"

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

