/* Copyright: (c) Kayne Ruse 2015
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "card_entry.hpp"
#include "csv_tool.hpp"
#include "formats.hpp"
#include "json.hpp"
#include "set_codes.hpp"
#include "utils.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

int usage(int argc, char* argv[]) {
	std::cout << "Usage: " << argv[0] << " FILE IFORMAT OFORMAT" << std::endl;
	std::cout << "Type \"" << argv[0] << " help\" for more info" << std::endl;
	return 0;
}

int help(int argc, char* argv[]) {
	//TODO: iomanip
	//print the help information
	std::cout << "Usage: " << argv[0] << " FILE IFORMAT OFORMAT" << std::endl;
	std::cout << "\tFILE\t\t- The name of the input file" << std::endl;
	std::cout << "\tIFORMAT\t\t- The input file's format" << std::endl;
	std::cout << "\tOFORMAT\t\t- The output file's format" << std::endl;
	std::cout << "Valid formats are:" << std::endl;
	std::cout << "\tCardbase\t- Cardbase standard CSV format" << std::endl;
	std::cout << "\tDeckbox\t\t- Deckbox.org standard CSV format" << std::endl;
	std::cout << "\tPucatrade\t- Pucatrade.com importer format" << std::endl;
	std::cout << "\tTappedout\t- Tappedout.net decklist format" << std::endl;
	return 0;
}

enum Format {
	CARDBASE = 1,
	DECKBOX = 2,
	PUCATRADE = 3,
	TAPPEDOUT = 4,

	FORMAT_ERROR
};

Format toFormat(const char* str) {
	//parse the input
	if (!stricmp(str, "cardbase")) {
		return Format::CARDBASE;
	}
	if (!stricmp(str, "deckbox")) {
		return Format::DECKBOX;
	}
	if (!stricmp(str, "pucatrade")) {
		return Format::PUCATRADE;
	}
	if (!stricmp(str, "tappedout")) {
		return Format::TAPPEDOUT;
	}
	return Format::FORMAT_ERROR;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		if (argc == 2 && !stricmp(argv[1], "help")) {
			return help(argc, argv);
		}
		return usage(argc, argv);
	}

	Format inputFormat = toFormat(argv[2]);
	Format outputFormat = toFormat(argv[3]);

	if (inputFormat == Format::FORMAT_ERROR) {
		std::cout << "Unknown IFORMAT" << std::endl;
		return 1;
	}

	if (outputFormat == Format::FORMAT_ERROR) {
		std::cout << "Unknown OFORMAT" << std::endl;
		return 1;
	}

	//DEBUG
	std::cout << "Formats: (" << inputFormat << ", " << outputFormat << ")" << std::endl;

	try {
		//get the rares list
		std::list<CardEntry> cardList;

		switch(inputFormat) {
			case Format::CARDBASE:
				cardList = readCardbaseCSV(readCSV<6>(argv[1], ';'));
			break;
			case Format::DECKBOX:
				//TODO: read deckbox.dek
//			break;
			case Format::PUCATRADE:
				//TODO: read pucatrade
//			break;
			case Format::TAPPEDOUT:
				//TODO: read tappedout

				//DEBUG: implementation warning
				std::cout << "Sorry, but this feature is incomplete" << std::endl;
				return 2;
			break;
		}

		//database
		nlohmann::json allCardsX = loadjson("rsc/AllCards-x.json");

		//verify the card list
		int errors = verifyCardList(cardList, allCardsX);

		std::cout << "Number of verification errors: " << errors << std::endl;

		//DEBUG: dump card list
		for (auto& it : cardList) {
			std::cout << it.name << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
