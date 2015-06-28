#include "json.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>

int main(int, char**) {
	//load the json file
	std::ifstream is("../rsc/AllCards.json");

	if (!is.is_open()) {
		std::cerr << "Failed to open the json file" << std::endl;
		return 1;
	}

	//load the json file
	nlohmann::json j;
	j << is;
	is.close();

/*	//testing
	for (auto it : j["KTK"]["cards"]) {
		//the json internals require the call to "dump()" to retrieve a plain string
		std::cout << std::setw(30) << std::left << it["name"].dump();

		//only print the mana cost if it's available
		if (it["manaCost"].type() != nlohmann::json::value_t::null) {
			std::cout << std::setw(30) << std::left << it["manaCost"].dump();
		}

		//clear output
		std::cout << std::endl;
	}
*/

	std::cout << j["Treasure Cruise"] << std::endl;
	//done
	return 0;
}