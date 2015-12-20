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

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

int usage(int argc, char* argv[]) {
	std::cout << "Usage: " << argv[0] << " COMMAND" << std::endl;
	std::cout << "Type \"" << argv[0] << " help\" for more information" << std::endl;
	return 0;
}

int about(int argc, char* argv[]) {
	//copyright
	std::cout << "Cardbase (c) Kayne Ruse 2015-2016" << std::endl;
	std::cout << "https://www.github.com/Ratstail91/Cardbase" << std::endl;
	std::cout << "Type \"" << argv[0] << " help\" for more information" << std::endl;
}

int help(int argc, char* argv[]) {
	if (argc == 2) {
		//print the help information
		std::cout << "Usage: " << argv[0] << " COMMAND" << std::endl;
		std::cout << "Available options are:" << std::endl;

		//about
		std::cout << std::left << std::setw(15) << "ABOUT";
		std::cout << std::left << "Show copyright information" << std::endl;

		//help
		std::cout << std::left << std::setw(15) << "HELP";
		std::cout << std::left << "Show this help message" << std::endl;

		//convert between file formats
		std::cout << std::left << std::setw(15) << convertHelp("command", argc, argv);
		std::cout << std::left << convertHelp("shorthelp", argc, argv) << std::endl;

		//list all known versions of a card
//		std::cout << std::left << std::setw(15) << "list";
//		std::cout << std::left << "List all printings of a card (incomplete)" << std::endl;

		//list all known versions of a card
//		std::cout << std::left << std::setw(15) << "list";
//		std::cout << std::left << "List all printings of a card (incomplete)" << std::endl;

		//list all known versions of a card
//		std::cout << std::left << std::setw(15) << "legality";
//		std::cout << std::left << "Lheck the legality of a card or decklist (incomplete)" << std::endl;

		//for more information...
		std::cout << "For more information about a specific command, type ";
		std::cout << argv[0] << " HELP COMMAND" << std::endl;
	}
	else {
		//specific command
		if ( !stricmp(argv[2], convertHelp("command", argc, argv).c_str()) ) {
			std::cout << convertHelp("longhelp", argc, argv) << std::endl;
		}
	}

	return 0;
}

int main(int argc, char* argv[]) {
	//no args
	if (argc == 1) {
		return usage(argc, argv);
	}

	//asking for info
	if (!stricmp(argv[1], "about")) {
		return about(argc, argv);
	}

	//asking for help
	if (!stricmp(argv[1], "help")) {
		return help(argc, argv);
	}

	//asking for conversion
//	if (!stricmp(argv[1], "convert")) {
//		return convert(argc, argv);
//	}

	std::cout << "Unknown command" << std::endl;
	std::cout << "Type \"" << argv[0] << " help\" for more information" << std::endl;

	return 0;
}
