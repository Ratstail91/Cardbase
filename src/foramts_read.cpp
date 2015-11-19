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
#include "formats.hpp"

#include <cstdlib>
#include <cstring>

#ifndef stricmp
#define stricmp(i, j) strcasecmp(i, j)
#endif

static std::string popQuotes(std::string s) {
	//remove the characters at the beginning & end of the string
	if (s.size() < 2) {
		return std::string("");
	}

	return s.substr(1, s.size()-2);
}

std::list<CardEntry> readCardbaseCSV(CSVObject<6> obj) {
	std::list<CardEntry> cardList;

	for (auto& it : obj) {
		CardEntry entry;

		//stringsatoi
		entry.name = it[0];
		entry.code = it[1];
		entry.language = it[2];

		//grade
		if (!stricmp(it[3].c_str(), "mint") || !stricmp(it[3].c_str(), "m")) {
			entry.grade = Grade::MINT;
		}
		else if (!stricmp(it[3].c_str(), "near mint") || !stricmp(it[3].c_str(), "nm")) {
			entry.grade = Grade::NEAR_MINT;
		}
		else if (!stricmp(it[3].c_str(), "lightly played") || !stricmp(it[3].c_str(), "lp")) {
			entry.grade = Grade::LIGHTLY_PLAYED;
		}
		else if (!stricmp(it[3].c_str(), "moderately played") || !stricmp(it[3].c_str(), "mp")) {
			entry.grade = Grade::MODERATELY_PLAYED;
		}
		else if (!stricmp(it[3].c_str(), "heavily played") || !stricmp(it[3].c_str(), "hp")) {
			entry.grade = Grade::HEAVILY_PLAYED;
		}
		else { //error
			entry.grade = Grade::ERROR;
		}

		//boolean
		if (!stricmp(it[4].c_str(), "true") || !stricmp(it[4].c_str(), "foil")) {
			entry.foil = true;
		}
		else {
			entry.foil = false;
		}

		//int
		entry.count = atoi(it[5].c_str());

		//finally
		cardList.push_back(entry);
	}

	return cardList;
}

std::list<CardEntry> readDeckboxCSV(CSVObject<6> obj) {
	//TODO: EMPTY
}

std::list<CardEntry> readPucatrade(std::list<std::string>) {
	//TODO: EMPTY
}

std::list<CardEntry> readTappedoutDEK(std::list<std::string>) {
	//TODO: EMPTY
}
