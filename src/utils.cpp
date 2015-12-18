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
#include "utils.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>

std::string pushQuotes(std::string s) {
	//add quote characters at the beginning & end of the string
	return std::string() + "\"" + s + "\"";
}

std::string popQuotes(std::string s) {
	//remove the characters at the beginning & end of the string
	if (s.size() < 2) {
		return std::string("");
	}

	return s.substr(1, s.size()-2);
}

std::string pruneSpace(std::string s) {
	//prune front
	while (s.size() && isspace(s[0])) {
		s = s.substr(1);
	}

	//prune back
	while (s.size() && isspace(s[ s.size()-1 ])) {
		s = s.substr(0, s.size()-1);
	}

	return s;
}

nlohmann::json loadjson(std::string str) {
	//load a file into a json object
	std::ifstream is(str);

	if (!is.is_open()) {
		std::ostringstream os;
		os << "Failed to open file: " << str;
		throw(std::runtime_error(os.str()));
	}

	nlohmann::json ret;
	ret << is;
	is.close();

	return ret;
}

std::list<std::string> readStringList(std::string fname) {
	//return object
	std::list<std::string> stringList;

	//open the file
	std::ifstream is(fname);

	if (!is.is_open()) {
		std::ostringstream msg;
		msg << "Failed to open file: " << fname;
		throw(std::runtime_error(msg.str()));
	}

	//for each
	while (!is.eof()) {
		std::string line;
		getline(is, line);
		if (line.size() != 0) {
			stringList.push_back(line);
		}
	}

	//finally
	return stringList;
}

void writeStringList(std::string fname, std::list<std::string> stringList) {
	//basic file output for a list of strings
	std::ofstream os(fname);

	//error check
	if (!os.is_open()) {
		std::ostringstream msg;
		msg << "Failed to open file: " << fname;
		throw(std::runtime_error(msg.str()));
	}

	//for each
	for (auto& it : stringList) {
		os << it << std::endl;
	}

	//finally
	os.close();
}

int verifyCardList(std::list<CardEntry> cardList, nlohmann::json allCardsX) {
	//ensure that the card list conforms to the given database (AllCards-x.json)
	int errors = 0;

	//for each card in the given list
	for (auto& it : cardList) {
		//check if the card is in the database
		if (allCardsX.find(it.name) == allCardsX.end()) {
			std::cout << "Unknown card name: " << it.name << std::endl;
			errors++;
			continue;
		}

		//get the card from the database
		nlohmann::json cardDB = allCardsX[it.name];

		//for each printing
		for (auto& p : cardDB["printings"]) {
			//if a printing matches the set code, move on
			if ( popQuotes(p.dump()) == it.code) {
				goto for_each_cardlist;
			}
		}

		//set code not found in database
		errors++;

		//output warning & offer solutions
		std::cout << "Unknown set code: " << it.name << " (" << it.code << ")" << std::endl;
		for (auto& i : cardDB["printings"]) {
			std::cout << "\t" << i << std::endl;
		}

for_each_cardlist:
		; //continue;
	}

	return errors;
}