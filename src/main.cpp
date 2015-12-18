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
#include <string>

int usage(int argc, char* argv[]) {
	std::cout << "Usage: " << argv[0] << " INFILE OUTFILE INFORMAT OUTFORMAT" << std::endl;
	std::cout << "Type \"" << argv[0] << " help\" for more info" << std::endl;
	return 0;
}

int help(int argc, char* argv[]) {
	//TODO: iomanip
	//print the help information
	std::cout << "Usage: " << argv[0] << " INFILE OUTFILE INFORMAT OUTFORMAT" << std::endl;
	std::cout << "\tINFILE\t\t- The name of the input file" << std::endl;
	std::cout << "\tOUTFILE\t\t- The name of the output file" << std::endl;
	std::cout << "\tINFORMAT\t\t- The input file's format" << std::endl;
	std::cout << "\tOUTFORMAT\t\t- The output file's format" << std::endl;
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

//collapse duplicate entries
void collapseList(std::list<CardEntry>& cardList) {
	std::list<CardEntry>::iterator it = cardList.begin();

	while (it != cardList.end()) {
		std::list<CardEntry>::iterator next = it;
		next++; //point to the next iterator

		//done
		if (next == cardList.end()) {
			break;
		}

		//add identical neighbours
		if (*it == *next) {
			it->count += next->count;
			cardList.erase(next);
			continue;
		}

		//move on
		it++;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		if (argc == 2 && !stricmp(argv[1], "help")) {
			return help(argc, argv);
		}
		return usage(argc, argv);
	}

	Format inputFormat = toFormat(argv[3]);
	Format outputFormat = toFormat(argv[4]);

	if (inputFormat == Format::FORMAT_ERROR) {
		std::cout << "Unknown INFORMAT" << std::endl;
		return 1;
	}

	if (outputFormat == Format::FORMAT_ERROR) {
		std::cout << "Unknown OUTFORMAT" << std::endl;
		return 1;
	}

	//DEBUG
	std::cout << "Formats: (" << inputFormat << ", " << outputFormat << ")" << std::endl;

	try {
		//database
		nlohmann::json allCardsX = loadjson("rsc/AllCards-x.json");

		//get the rares list
		std::list<CardEntry> cardList;

		switch(inputFormat) {
			case Format::CARDBASE:
				cardList = readCardbaseCSV(readCSV<6>(argv[1], ';'));
			break;
			case Format::TAPPEDOUT:
				cardList = readTappedoutDEK(readStringList(argv[1]));
			break;

			//TODO: read deckbox.dek
			case Format::DECKBOX:
			//TODO: read pucatrade
			case Format::PUCATRADE:
			default:
				std::cout << "Sorry, but this feature is incomplete" << std::endl;
				return 2;
		}

		//verify the card list
		int errors = verifyCardList(cardList, allCardsX);

		//sort & collapse the card list
		cardList.sort();
		collapseList(cardList);

		std::cout << "Number of verification errors: " << errors << std::endl;

		//write the output file
		switch(outputFormat) {
			case Format::CARDBASE:
				writeCSV<6>(argv[2], writeCardbaseCSV(cardList), ';');
			break;
			case Format::DECKBOX:
				writeCSV<6>(argv[2], writeDeckboxCSV(cardList), ',');
			break;
			case Format::TAPPEDOUT:
				writeStringList(argv[2],writeTappedoutDEK(cardList));
			break;

			//TODO: pucatrade ouput
			case Format::PUCATRADE:
			default:
				std::cout << "Sorry, but this feature is incomplete" << std::endl;
				return 2;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
