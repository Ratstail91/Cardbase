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
#include "format.hpp"

#include "json.hpp"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

#ifndef stricmp
#define stricmp(i, j) strcasecmp(i, j)
#endif

CardList readCSV(std::string fname) {
	//open
	std::fstream is(fname);

	if (!is.is_open()) {
		std::ostringstream msg;
		msg << "Failed to open CSV: " << fname;
		throw(std::runtime_error(msg.str()));
	}

	//read into fileLines
	std::list<std::string> fileLines;
	std::string tmpString;
	while(!is.eof()) {
		std::getline(is, tmpString);
		fileLines.push_back(tmpString);
	}

	is.close();

	//interpret the lines into 
	CardList cardList;
	std::for_each(fileLines.begin(), fileLines.end(), [&cardList](std::string line) {
		if (line.size() == 0 || line[0] == '#') {
			return;
		}

		char name[256];
		char code[256];
		char language[256];
		char foil[256];
		int count = 0;
		char grade[256];

		memset(name, 0, 256);
		memset(code, 0, 256);
		memset(language, 0, 256);
		memset(foil, 0, 256);
		memset(grade, 0, 256);

		int fieldCount = sscanf(line.c_str(), "%[^;];%[^;];%[^;];%[^;];%d;%[^;\n]",
			name,
			code,
			language,
			foil,
			&count,
			grade
			);

		if (fieldCount < 2) {
			std::ostringstream msg;
			msg << "Missing mandatory field (found " << fieldCount << "): " << line << std::endl;
			msg << "Note: " << name << std::endl;
			msg << "Note: " << code << std::endl;
			msg << "Note: " << language << std::endl;
			throw(std::runtime_error(msg.str()));
		}

		//set fields
		CardStruct cardStruct;

		cardStruct.name = name;
		cardStruct.code = code;
		if (fieldCount < 3) {
			goto end;
		}

		//language
		cardStruct.language = language;
		if (fieldCount < 4) {
			goto end;
		}

		//foil
		if (!stricmp(foil, "true") || !stricmp(foil, "foil")) {
			cardStruct.foil = true;
		}
		else if (!stricmp(foil, "false")) {
			cardStruct.foil = false;
		}
		else {
			std::ostringstream msg;
			msg << "Unknown value (foil): " << foil;
			throw(std::runtime_error(msg.str()));
		}
		if (fieldCount < 5) {
			goto end;
		}

		//count
		cardStruct.count = count;
		if (fieldCount < 6) {
			goto end;
		}

		//grade
		if (!stricmp(grade, "m") || !stricmp(grade, "mint")) {
			cardStruct.grade = CardGrade::MINT;
		}
		else if (!stricmp(grade, "nm") || !stricmp(grade, "near mint")) {
			cardStruct.grade = CardGrade::NEAR_MINT;
		}
		else if (!stricmp(grade, "lp") || !stricmp(grade, "lightly played")) {
			cardStruct.grade = CardGrade::LIGHTLY_PLAYED;
		}
		else if (!stricmp(grade, "mp") || !stricmp(grade, "moderatly played")) {
			cardStruct.grade = CardGrade::MODERATELY_PLAYED;
		}
		else if (!stricmp(grade, "hp") || !stricmp(grade, "heavily played")) {
			cardStruct.grade = CardGrade::HEAVILY_PLAYED;
		}
		else if (!stricmp(grade, "e") || !stricmp(grade, "error") || !stricmp(grade, "misprint")) {
			cardStruct.grade = CardGrade::ERROR;
		}
		else {
			std::ostringstream msg;
			msg << "Unknown value (grade): " << grade;
			throw(std::runtime_error(msg.str()));
		}

end:
		cardList.push_back(cardStruct);
	});

	return cardList;
}