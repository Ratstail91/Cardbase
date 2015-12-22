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
#include "list.hpp"

#include "card_entry.hpp"
#include "csv_tool.hpp"
#include "json.hpp"
#include "utils.hpp"

#include <iomanip>
#include <iostream>
#include <list>
#include <string>

const std::string command = "LIST";
const std::string shorthelp = "list all known versions of a card";
const std::string longhelp = "";

std::string listHelp(const char* mode, int argc, char* argv[]) {
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
		str += std::string() + "Usage: " + argv[0] + " " + command + " card_name";
		return str;
	}
	//error
	return "";
}

//-------------------------
//implement the command itself
//-------------------------

int list(int argc, char* argv[]) {
	//database
	//TODO: slow as f*ck, needs to load ~65MB into memory for this simple operation
	nlohmann::json allCardsX = loadjson("rsc/AllCards-x.json");
	nlohmann::json allSetsX = loadjson("rsc/StrippedSets-x.json");

	//check the spelling
	if (allCardsX[argv[2]].is_null()) {
		std::cout << "Could not find the card \"" << argv[2] << "\"" << std::endl;
		return 0;
	}

	std::string setCode;
	std::string setName;

	for (auto& it : allCardsX[argv[2]]["printings"]) {
		setCode = it.get<std::string>();
		setName = allSetsX[setCode]["name"].get<std::string>();

		//formatting
		std::cout << std::left << std::setw(10) << setCode << setName << std::endl;
	}

	return 0;
}