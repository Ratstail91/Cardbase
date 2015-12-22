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
#include "json.hpp"

#include <fstream>
#include <iostream>

nlohmann::json loadjson(std::string str) {
	//load a file into a json object
	std::ifstream is(str);

	if (!is.is_open()) {
		std::ostringstream msg;
		msg << "Failed to open file: " << str;
		throw(std::runtime_error(msg.str()));
	}

	nlohmann::json ret;
	ret << is;
	is.close();

	return ret;
}

int savejson(nlohmann::json obj, std::string str) {
	//save a json object into a file
	std::ofstream os(str);

	if (!os.is_open()) {
		std::ostringstream msg;
		msg << "Failed to open file: " << str;
		throw(std::runtime_error(msg.str()));
	}

	os << obj;
	os.close();

	return 0;
}

int main(int argc, char* argv[]) {
	std::cout << "Beginning " << argv[0] << std::endl;

	nlohmann::json allSetsX = loadjson("rsc/AllSets-X.json");

	for (nlohmann::json::iterator set = allSetsX.begin(); set != allSetsX.end(); set++) {
		set->erase("cards");
	}

	//dump
	savejson(allSetsX, "rsc/StrippedSets-x.json");

	std::cout << "Finished " << argv[0] << std::endl;
	return 0;
}