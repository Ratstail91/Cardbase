#pragma once

#include <map>
#include <string>
 
//DOCS: some sets may be missing, or this may be out of date
const std::map<std::string, std::string> conversions = {
	//core sets
	{"(LEA)", "Limited Edition Alpha"},
	{"(LEB)", "Limited Edition Beta"},
	{"(2ED)", "Unlimited Edition"},
	{"(3ED)", "Revised Edition"},
	{"(4ED)", "Fourth Edition"},
	{"(5ED)", "Fifth Edition"},
	{"(6ED)", "Classic Sixth Edition"},
	{"(7ED)", "Seventh Edition"},
	{"(8ED)", "Eighth Edition"},
	{"(9ED)", "Ninth Edition"},
	{"(10E)", "Tenth Edition"},
	{"(M10)", "Magic 2010"},
	{"(M11)", "Magic 2011"},
	{"(M12)", "Magic 2012"},
	{"(M13)", "Magic 2013"},
	{"(M14)", "Magic 2014 Core Set"},
	{"(M15)", "Magic 2015 Core Set"},
	{"(ORI)", "Magic Origins"},

	//sets-blocks
	{"(ARN)", "Arabian Nights"},
	{"(ATQ)", "Antiquities"},
	{"(LEG)", "Legends"},
	{"(DRK)", "The Dark"},
	{"(FEM)", "Fallen Empires"},
	{"(HML)", "Homelands"},

	{"(ICE)", "Ice Age"},
	{"(ALL)", "Alliances"},
	{"(CSP)", "Coldsnap"},

	{"(MIR)", "Mirage"},
	{"(VIS)", "Visions"},
	{"(WTH)", "Weatherlight"},

	{"(TMP)", "Tempest"},
	{"(STH)", "Stronghold"},
	{"(EXO)", "Exodus"},

	{"(USG)", "Urza's Saga"},
	{"(ULG)", "Urza's Legacy"},
	{"(UDS)", "Urza's Destiny"},

	{"(MMQ)", "Mercadian Masques"},
	{"(NMS)", "Nemesis"},
	{"(PCY)", "Prophesy"},

	{"(INV)", "Invasion"},
	{"(PLS)", "Planeshift"},
	{"(APC)", "Apocalypse"},

	{"(ODY)", "Odyssey"},
	{"(TOR)", "Torment"},
	{"(JUD)", "Judgment"},

	{"(ONS)", "Onslaught"},
	{"(LGN)", "Legions"},
	{"(SCG)", "Scourge"},

	{"(MRD)", "Mirrodin"},
	{"(DST)", "Darksteel"},
	{"(5DN)", "Fifth Dawn"},

	{"(CHK)", "Champions of Kamigawa"},
	{"(BOK)", "Betrayers of Kamigawa"},
	{"(SOK)", "Saviors of Kamigawa"},

	{"(RAV)", "Ravnica: City of Guilds"},
	{"(GPT)", "Guildpact"},
	{"(DIS)", "Dissension"},

	{"(TSB)", "Timeshifted"}, //timeshifted cards
	{"(TSP)", "Time Spiral"},
	{"(PLC)", "Planar Chaos"},
	{"(FUT)", "Future Sight"},

	{"(LRW)", "Lorwyn"},
	{"(MOR)", "Morningtide"},
	{"(SHM)", "Shadowmoor"},
	{"(EVE)", "Eventide"},

	{"(ALA)", "Shards of Alara"},
	{"(CON)", "Conflux"},
	{"(ARB)", "Alara Reborn"},

	{"(ZEN)", "Zendikar"},
	{"(WWK)", "Worldwake"},
	{"(ROE)", "Rise of the Eldrazi"},

	{"(SOM)", "Scars of Mirrodin"},
	{"(MBS)", "Mirrodin Besieged"},
	{"(NPH)", "New Phyrexia"},

	{"(ISD)", "Innistrad"},
	{"(DKA)", "Dark Ascension"},
	{"(AVR)", "Avacyn Restored"},

	{"(RTR)", "Return to Ravnica"},
	{"(GTC)", "Gatecrash"},
	{"(DGM)", "Dragon's Maze"},

	{"(THS)", "Theros"},
	{"(BNG)", "Born of the Gods"},
	{"(JOU)", "Journey into Nyx"},

	{"(KTK)", "Khans of Tarkir"},
	{"(FRF)", "Fate Reforged"},
	{"(DTK)", "Dragons of Tarkir"},

	{"(BFZ)", "Battle for Zendikar"},
	{"(OGW)", "Oath of the Gatewatch"}, //next set

	//reprint sets
	{"(CHR)", "Chronicles"},
	{"(ATH)", "Anthologies"},
	{"(BRB)", "Battle Royale Box Set"},
	{"(BTD)", "Beatdown Box Set"},
	{"(DKM)", "Deckmasters: Garfield vs. Finkel"},
	{"(DPA)", "Duels of the Planeswalkers"},
	{"(ARC)", "Archenemy"},
	{"(MMA)", "Modern Masters"},
	{"(MM2)", "Modern Masters 2015 Edition"},
	{"(---)", "Renaissance"}, //french/german
	{"(---)", "Renascimento"}, //italian

	{"(EVG)", "Duel Decks: Elves vs. Goblins"},
	{"(DD2)", "Duel Decks: Jace vs. Chandra"},
	{"(DDC)", "Duel Decks: Divine vs. Demonic"},
	{"(DDD)", "Duel Decks: Garruk vs. Liliana"},
	{"(DDE)", "Duel Decks: Phyrexia vs. the Coalition"},
	{"(DDF)", "Duel Decks: Elspeth vs. Tezzeret"},
	{"(DDG)", "Duel Decks: Knights vs. Dragons"},
	{"(DDH)", "Duel Decks: Ajani vs. Nicol Bolas"},
	{"(DDI)", "Duel Decks: Venser vs. Koth"},
	{"(DDJ)", "Duel Decks: Izzet vs. Golgari"},
	{"(DDK)", "Duel Decks: Sorin vs. Tibalt"},
	{"(DDL)", "Duel Decks: Heroes vs. Monsters"},
	{"(DDM)", "Duel Decks: Jace vs. Vraska"},
	{"(DDN)", "Duel Decks: Speed vs. Cunning"},
	{"(DD3)", "Duel Decks Anthology"},
	{"(DDO)", "Duel Decks: Elspeth vs. Kiora"},
	{"(DDP)", "Duel Decks: Zendikar vs. Eldrazi"},
	{"(???)", "Duel Decks: Blessed vs. Cursed"},

	{"(DRB)", "From the Vault: Dragons"},
	{"(V09)", "From the Vault: Exiled"},
	{"(V10)", "From the Vault: Relics"},
	{"(V11)", "From the Vault: Legends"},
	{"(V12)", "From the Vault: Realms"},
	{"(V13)", "From the Vault: Twenty"},
	{"(V14)", "From the Vault: Annihilation"},
	{"(V15)", "From the Vault: Angels"},

	{"(H09)", "Premium Deck Series: Slivers"},
	{"(PD2)", "Premium Deck Series: Fire and Lightning"},
	{"(PD3)", "Premium Deck Series: Graveborn"},

	{"(MD1)", "Modern Event Deck 2014"},

	//non-standard-legal sets
	{"(HOP)", "Planechase"},
	{"(PC2)", "Planechase 2012 Edition"},
	{"(CMD)", "Commander"},
	{"(CM1)", "Commander's Arsenal"},
	{"(C13)", "Commander 2013 Edition"},
	{"(C14)", "Commander 2014"},
	{"(C15)", "Commander 2015"},
	{"(CNS)", "Conspiracy"},

	//intro sets
	{"(POR)", "Portal"},
	{"(PO2)", "Portal Second Age"},
	{"(PTK)", "Portal Three Kingdoms"},
	{"(S99)", "Starter 1999"},
	{"(S00)", "Starter 2000"},

	//silver-boarder sets
	{"(UGL)", "Unglued"},
	{"(UNH)", "Unhinged"},

	//non-sets
	{"(FNM)", "FNM Promo"},
	{"(000)", "Unknown Set"},
};