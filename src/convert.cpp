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
#include "convert.hpp"

#include "card_entry.hpp"
#include "csv_tool.hpp"
#include "formats.hpp"
#include "json.hpp"
#include "utils.hpp"

#include <list>
#include <string>

const std::string command = "CONVERT";
const std::string shorthelp = "Convert from one file format to another";
const std::string longhelp = "Valid formats are:\n\
  Cardbase     Cardbase proprietary CSV format, for internal use.\n\
  Deckbox      Deckbox.org CSV format, supported by a number of services.\n\
  MTGO         Magic: The Gathering Online file format.\n\
  Pucatrade    Pucatrade import/export file format, not currently supported.\n\
  Tappedout    Tappedout.net DEK format, a simple human readable format.\n\
";

std::string convertHelp(const char* mode, int argc, char* argv[]) {
	//name of the command
	if (!stricmp("command", mode)) {
		return command;
	}
	//summary
	if (!stricmp("shorthelp", mode)) {
		return shorthelp;
	}
	//details
	if (!stricmp("longhelp", mode)) {
		//build the help message
		std::string str;
		str += shorthelp + "\n";
		str += std::string() + "Usage: " + argv[0] + " " + command + " input_file output_file input_format output_format\n";
		str += longhelp;
		return str;
	}
	//error
	return "";
}

//-------------------------
//implement the command itself
//-------------------------

enum Format {
	CARDBASE = 1,
	DECKBOX = 2,
	MTGO = 3,
	PUCATRADE = 4,
	TAPPEDOUT = 5,

	FORMAT_ERROR
};

//string to format
Format toFormat(const char* str) {
	//parse the input
	if (!stricmp(str, "cardbase")) {
		return Format::CARDBASE;
	}
	if (!stricmp(str, "deckbox")) {
		return Format::DECKBOX;
	}
	if (!stricmp(str, "mtgo")) {
		return Format::MTGO;
	}
	if (!stricmp(str, "pucatrade")) {
		return Format::PUCATRADE;
	}
	if (!stricmp(str, "tappedout")) {
		return Format::TAPPEDOUT;
	}
	return Format::FORMAT_ERROR;
}

//args: argv[0] convert inlist outlist informat outformat
int convert(int argc, char* argv[]) {
	//get the formats
	Format inputFormat = toFormat(argv[4]);
	Format outputFormat = toFormat(argv[5]);

	if (inputFormat == Format::FORMAT_ERROR) {
		std::cout << "Unknown input_format" << std::endl;
		return 1;
	}

	if (outputFormat == Format::FORMAT_ERROR) {
		std::cout << "Unknown output_format" << std::endl;
		return 1;
	}

	//DEBUG
	std::cout << "Formats: (" << inputFormat << ", " << outputFormat << ")" << std::endl;

	try {
		//database
		nlohmann::json allCardsX = loadjson("rsc/AllCards-x.json");

		//internal card list
		std::list<CardEntry> cardList;

		switch(inputFormat) {
			case Format::CARDBASE:
				cardList = readCardbaseCSV(readCSV<6>(argv[2], ';'));
			break;
			case Format::TAPPEDOUT:
				cardList = readTappedoutDEK(readStringList(argv[2]));
			break;

			//TODO: read deckbox.dek
			case Format::DECKBOX:
			//TODO: read MTGO.dek
			case Format::MTGO:
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
				writeCSV<6>(argv[3], writeCardbaseCSV(cardList), ';');
			break;
			case Format::DECKBOX:
				writeCSV<6>(argv[3], writeDeckboxCSV(cardList), ',');
			break;
			case Format::TAPPEDOUT:
				writeStringList(argv[3],writeTappedoutDEK(cardList));
			break;

			//TODO: write MTGO.dek
			case Format::MTGO:
			//TODO: write pucatrade
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
}