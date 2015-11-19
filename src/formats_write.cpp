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

#include <sstream>

CSVObject<6> writeCardbaseCSV(std::list<CardEntry> cardList) {
	CSVObject<6> obj;

	for (auto& it : cardList) {
		CSVElement<6> record;

		//strings
		record[0] = it.name;
		record[1] = it.code;
		record[2] = it.language;

		//enum
		record[3] = [it]() -> std::string {
			switch(it.grade) {
				case Grade::MINT: return "M";
				case Grade::NEAR_MINT: return "NM";
				case Grade::LIGHTLY_PLAYED: return "LP";
				case Grade::MODERATELY_PLAYED: return "MP";
				case Grade::HEAVILY_PLAYED: return "HP";
			}
			return "error";
		}();

		//boolean
		record[4] = it.foil ? "true" : "false";

		//integer
		char buf[16];
		sprintf(buf, "%d", it.count);
		record[5] = buf;

		obj.push_back(record);
	}

	return obj;
}

CSVObject<6> writeDeckboxCSV(std::list<CardEntry> cardList) {
	//TODO: EMPTY
}

std::list<std::string> writePucatrade(std::list<CardEntry> cardList) {
	//TODO: EMPTY
}

std::list<std::string> writeTappedoutDEK(std::list<CardEntry> cardList) {
	std::list<std::string> ret;

	for (auto& it : cardList) {
		std::ostringstream os;

		//count, name
		os << it.count << "x " << it.name;
		if (it.foil) {
			os << " *F*";
		}
		os << " (" << it.code << ")";

		ret.push_back(os.str());
	}

	return ret;
}
