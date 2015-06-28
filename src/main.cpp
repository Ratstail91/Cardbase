#include "json.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>

//TODO: print name...

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

	//fields
	for (nlohmann::json::iterator it = j.begin(); it != j.end(); it++) {

		std::cout << std::setw(25) << std::left << (*it)["name"].dump().substr(0, 20);
		std::cout << std::setw(25) << std::left << (*it)["manaCost"].dump().substr(0, 20);
		std::cout << std::setw(25) << std::left << (*it)["type"].dump().substr(0, 20);
		std::cout << std::endl;
	}

	//done
	return 0;
}