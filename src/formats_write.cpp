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
#include "set_codes.hpp"
#include "utils.hpp"

#include <cstdlib>
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
		CSVObject<6> obj;
		CSVElement<6> header;

		//build & insert the header record
		header[0] = "Count";
		header[1] = "Name";
		header[2] = "Foil";
		header[3] = "Edition";
		header[4] = "Condition";
		header[5] = "Language";

		obj.push_back(header);

	for (auto& it : cardList) {
		CSVElement<6> record;

		//count, name
		char countBuffer[16];
		sprintf(countBuffer, "%d", it.count);
		record[0] = countBuffer;
		record[1] = pushQuotes(it.name);

		//foil
		if (it.foil) {
			record[2] = "foil";
		}

		//edition
		for (auto& set : setCodes) {
			if (set.first == it.code) {
				record[3] = set.second;
			}
		}
		if (record[3].size() == 0) {
			//not found
			record[3] = setCodes.at("000");
		}

		//condition
		switch(it.grade) {
			case Grade::MINT:
				record[4] = "Mint";
			break;
			case Grade::NEAR_MINT:
				record[4] = "Near Mint";
			break;
			case Grade::LIGHTLY_PLAYED:
				record[4] = "Good (Lightly Played)";
			break;
			case Grade::MODERATELY_PLAYED:
				record[4] = "Played";
			break;
			case Grade::HEAVILY_PLAYED:
				record[4] = "Heavily Played";
			break;
			case Grade::GRADE_ERROR:
				record[4] = "Poor";
			break;
		}

		//language
		record[5] = it.language;

		obj.push_back(record);
	}

	return obj;
}

std::list<std::string> writePucatrade(std::list<CardEntry> cardList) {
	//TODO: writePucatrade() empty
}

std::list<std::string> writeTappedoutDEK(std::list<CardEntry> cardList) {
	//TODO: writeTappedoutDEK incomplete
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
