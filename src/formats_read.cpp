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
#include "utils.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>

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
			entry.grade = Grade::GRADE_ERROR;
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
	//TODO: readDeckboxCSV() empty
}

std::list<CardEntry> readPucatrade(std::list<std::string>) {
	//TODO: readPucatrade() empty
}

/* DOCS: here's the "official" tappedout.net spec as far as I can tell (read more)
	In addition to these, they can be placed in any order on the line
	This is gonna be hard as hell.

	Any number to define the count
	[XXX] XXX printing
	*F* foil
	*A* altered
	*NM* condition (M = Mint, NM = Near Mint, SL = Slightly Played, P = Played)
	*DE* different languages (https://en.wikipedia.org/wiki/ISO_3166-1, alpha-2)
*/

std::list<CardEntry> readTappedoutDEK(std::list<std::string> stringList) {
	//TODO: readTappedoutDEK() incomplete
	std::list<CardEntry> cardList;

	for (auto& it : stringList) {
		CardEntry entry;
		char nameBuffer[512], codeBuffer[512];
		memset(nameBuffer, 0, 512);
		memset(codeBuffer, 0, 512);

		//read entry
		int r = sscanf(it.c_str(), "%dx %[^(](%[^)])", &entry.count, nameBuffer, codeBuffer);

		if (r != 3) {
			std::ostringstream msg;
			msg << "Failed to read a card: " << it;
			throw(std::runtime_error(msg.str()));
		}

		entry.name = pruneSpace(nameBuffer);
		entry.code = codeBuffer;

		//finally
		cardList.push_back(entry);
	}

	return cardList;
}
