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

#include "card_entry.hpp"
#include "csv_tool.hpp"

#include <list>
#include <string>

//DOCS: Format access; these functions convert list<cardEntry> to and from various other data structures based on format

//read
std::list<CardEntry> readCardbaseCSV(CSVObject<6> obj);
std::list<CardEntry> readDeckboxCSV(CSVObject<6> obj);
std::list<CardEntry> readPucatrade(std::list<std::string>);
std::list<CardEntry> readTappedoutDEK(std::list<std::string>);

//write
CSVObject<6> writeCardbaseCSV(std::list<CardEntry> cardList);
CSVObject<6> writeDeckboxCSV(std::list<CardEntry> cardList);
std::list<std::string> writePucatrade(std::list<CardEntry> cardList);
std::list<std::string> writeTappedoutDEK(std::list<CardEntry> cardList);
