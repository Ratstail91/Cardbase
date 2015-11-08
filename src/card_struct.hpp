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
#pragma once

#include <list>
#include <string>

enum CardGrade {
	MINT = 1,
	NEAR_MINT = 2,
	LIGHTLY_PLAYED = 3,
	MODERATELY_PLAYED = 4,
	HEAVILY_PLAYED = 5,
	ERROR = 99
};

struct CardStruct {
	std::string name;
	std::string code;
	std::string language = "English";
	bool foil = false;
	int count = 0;
	CardGrade grade = CardGrade::NEAR_MINT;
};

typedef std::list<CardStruct> CardList;