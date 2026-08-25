CeladonCity_Hotel_Frlg_MapScripts::
	.byte 0

CeladonCity_Hotel_EventScript_Receptionist::
	msgbox CeladonCity_Hotel_Text_ThisHotelIsForPeople, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_Beauty::
	msgbox CeladonCity_Hotel_Text_OnVacationWithBrotherAndBoyfriend, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_BeautyBoyfriend::
	msgbox CeladonCity_Hotel_Text_WhyDidSheBringBrother, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_BeautyBrother::
	msgbox CeladonCity_Hotel_Text_SisBroughtMeOnVacation, MSGBOX_NPC
	end

CeladonCity_Hotel_Text_ThisHotelIsForPeople::
	.string "POKéMON?\n"
	.string "No, this is a hotel for people.\p"
	.string "We're full up, unfortunately.$"

CeladonCity_Hotel_Text_OnVacationWithBrotherAndBoyfriend::
	.string "I'm on vacation with my brother and\n"
	.string "boyfriend.\p"
	.string "I can't say why, but this city sits\n"
	.string "so easy on me.\p"
	.string "They say it's on the wind. …I've\n"
	.string "stopped asking why.$"

CeladonCity_Hotel_Text_WhyDidSheBringBrother::
	.string "Why did she bring\n"
	.string "her little brother?\p"
	.string "I planned this for two…$"

CeladonCity_Hotel_Text_SisBroughtMeOnVacation::
	.string "Vacation! Sis brought me\n"
	.string "to the big city!\p"
	.string "Her friend just sighs and\n"
	.string "sighs. Weird guy.$"

