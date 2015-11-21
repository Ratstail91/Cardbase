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
#include "card_entry.hpp"

#include <iostream>

bool operator<(CardEntry const& lhs, CardEntry const& rhs) {
	//check name
	int cmp = lhs.name.compare(rhs.name);
	if (cmp != 0) {
		return cmp < 0;
	}

	//check code
	cmp = lhs.code.compare(rhs.code);
	if (cmp != 0) {
		return cmp < 0;
	}

	//check language
	cmp = lhs.language.compare(rhs.language);
	if (cmp != 0) {
		return cmp < 0;
	}

	//non-foil before foil
	if (lhs.foil != rhs.foil) {
		return rhs.foil;
	}

	//lower grade value before higher (mint = 1, etc.)
	if (lhs.grade != rhs.grade) {
		return lhs.grade < rhs.grade;
	}

	//entries are identical, except for count
	return false;
}