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
#include "card_struct.hpp"
#include "format.hpp"
#include "json.hpp"

#include <iomanip>
#include <iostream>

int main(int argc, char* argv[]) {
	//read a card list
	CardList cardList = readCSV("/home/kayne/Dropbox/rare inventory");

	//print the loaded data
	for (auto& it : cardList) {
		std::cout << std::left << std::setw(32) << it.name;
		std::cout << std::left << std::setw(8) << it.code;

		//special conditions
		if (it.foil) {
			std::cout << "Foil";

			if (it.grade > CardGrade::NEAR_MINT) {
				std::cout << ", ";
			}
		}

		if (it.grade > CardGrade::NEAR_MINT) {
			switch(it.grade) {
				case CardGrade::LIGHTLY_PLAYED:
					std::cout << "Lightly Played";
				break;
				case CardGrade::MODERATELY_PLAYED:
					std::cout << "Moderately Played";
				break;
				case CardGrade::HEAVILY_PLAYED:
					std::cout << "Heavily Played";
				break;
				case CardGrade::ERROR:
					std::cout << "Grading Error";
				break;
			}
		}

		std::cout << std::endl;
	}

	return 0;
}