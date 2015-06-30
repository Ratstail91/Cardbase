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
#include "example_scene.hpp"

#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>

ExampleScene::ExampleScene() {
	//Testing this on ubuntu
	font = TTF_OpenFont(("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"), 12);

	if (!font) {
		throw(std::runtime_error("Failed to load font file"));
	}

	//graphics
	masterManaSheet.Load(GetRenderer(), "../rsc/Mana.png");
	CreateIndex();

	//read and store the .json file
	std::ifstream is("../rsc/AllCards.json");

	if (!is.is_open()) {
		throw(std::runtime_error("Failed to open the json file for reading"));
	}
	cardData << is;
	is.close();
}

ExampleScene::~ExampleScene() {
	DestroyIndex();
	TTF_CloseFont(font);
}

//-------------------------
//frame phases
//-------------------------

void ExampleScene::FrameStart() {
	//
}

void ExampleScene::Update() {
	//
}

void ExampleScene::FrameEnd() {
	//
}

void ExampleScene::RenderFrame(SDL_Renderer* renderer) {
	int line = 0;
	for (auto& it : cardData) {
		//render name
		RenderText(renderer, it["name"], 32, 32 + 16 * line);

		//render mana (if applicable)
		if (it["manaCost"].type() != nlohmann::json::value_t::null) {
			RenderManaCost(renderer, it["manaCost"], 300, 32 + 16 * line);
		}

		//debug
		if (line++ > 50) break;
	}

	//testing the mana display
//	manaIndex.at("G")->DrawTo(renderer, 32, 300, .2, .2);
}

//-------------------------
//input events
//-------------------------

void ExampleScene::MouseMotion(SDL_MouseMotionEvent const& event) {
	//
}

void ExampleScene::MouseButtonDown(SDL_MouseButtonEvent const& event) {
	//
}

void ExampleScene::MouseButtonUp(SDL_MouseButtonEvent const& event) {
	//
}

void ExampleScene::MouseWheel(SDL_MouseWheelEvent const& event) {
	//
}

void ExampleScene::KeyDown(SDL_KeyboardEvent const& event) {
	//preference as a default
	switch(event.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;
	}
}

void ExampleScene::KeyUp(SDL_KeyboardEvent const& event) {
	//
}

//-------------------------
//misc
//-------------------------

void ExampleScene::PopulateIndex(std::string name, SDL_Rect coords) {
	manaIndex[name] = new Image(masterManaSheet.GetTexture());
	manaIndex[name]->SetClip(coords);
}

void ExampleScene::CreateIndex() {
	//colorless numbers
	PopulateIndex("0", SDL_Rect{105*0, 105*0, 100, 100});
	PopulateIndex("1", SDL_Rect{105*1, 105*0, 100, 100});
	PopulateIndex("2", SDL_Rect{105*2, 105*0, 100, 100});
	PopulateIndex("3", SDL_Rect{105*3, 105*0, 100, 100});
	PopulateIndex("4", SDL_Rect{105*4, 105*0, 100, 100});
	PopulateIndex("5", SDL_Rect{105*5, 105*0, 100, 100});
	PopulateIndex("6", SDL_Rect{105*6, 105*0, 100, 100});
	PopulateIndex("7", SDL_Rect{105*7, 105*0, 100, 100});
	PopulateIndex("8", SDL_Rect{105*8, 105*0, 100, 100});
	PopulateIndex("9", SDL_Rect{105*9, 105*0, 100, 100});
	PopulateIndex("10", SDL_Rect{105*0, 105*1, 100, 100});
	PopulateIndex("11", SDL_Rect{105*1, 105*1, 100, 100});
	PopulateIndex("12", SDL_Rect{105*2, 105*1, 100, 100});
	PopulateIndex("13", SDL_Rect{105*3, 105*1, 100, 100});
	PopulateIndex("14", SDL_Rect{105*4, 105*1, 100, 100});
	PopulateIndex("15", SDL_Rect{105*5, 105*1, 100, 100});
	PopulateIndex("16", SDL_Rect{105*6, 105*1, 100, 100});
	PopulateIndex("17", SDL_Rect{105*7, 105*1, 100, 100});
	PopulateIndex("18", SDL_Rect{105*8, 105*1, 100, 100});
	PopulateIndex("19", SDL_Rect{105*9, 105*1, 100, 100});
	PopulateIndex("20", SDL_Rect{105*0, 105*2, 100, 100});

	//X, Y & Z
	PopulateIndex("X", SDL_Rect{105*1, 105*2, 100, 100});
	PopulateIndex("Y", SDL_Rect{105*2, 105*2, 100, 100});
	PopulateIndex("Z", SDL_Rect{105*3, 105*2, 100, 100});

	//basic land types
	PopulateIndex("W", SDL_Rect{105*4, 105*2, 100, 100});
	PopulateIndex("U", SDL_Rect{105*5, 105*2, 100, 100});
	PopulateIndex("B", SDL_Rect{105*6, 105*2, 100, 100});
	PopulateIndex("R", SDL_Rect{105*7, 105*2, 100, 100});
	PopulateIndex("G", SDL_Rect{105*8, 105*2, 100, 100});
	PopulateIndex("S", SDL_Rect{105*9, 105*2, 100, 100});

	//hybrid mana
	PopulateIndex("W/U", SDL_Rect{105*0, 105*3, 100, 100});
	PopulateIndex("W/B", SDL_Rect{105*1, 105*3, 100, 100});
	PopulateIndex("U/B", SDL_Rect{105*2, 105*3, 100, 100});
	PopulateIndex("U/R", SDL_Rect{105*3, 105*3, 100, 100});
	PopulateIndex("B/R", SDL_Rect{105*4, 105*3, 100, 100});
	PopulateIndex("B/G", SDL_Rect{105*5, 105*3, 100, 100});
	PopulateIndex("R/W", SDL_Rect{105*6, 105*3, 100, 100});
	PopulateIndex("R/G", SDL_Rect{105*7, 105*3, 100, 100});
	PopulateIndex("G/W", SDL_Rect{105*8, 105*3, 100, 100});
	PopulateIndex("G/U", SDL_Rect{105*9, 105*3, 100, 100});

	//multicost mana
	PopulateIndex("2/W", SDL_Rect{105*0, 105*4, 100, 100});
	PopulateIndex("2/U", SDL_Rect{105*1, 105*4, 100, 100});
	PopulateIndex("2/B", SDL_Rect{105*2, 105*4, 100, 100});
	PopulateIndex("2/R", SDL_Rect{105*3, 105*4, 100, 100});
	PopulateIndex("2/G", SDL_Rect{105*4, 105*4, 100, 100});

	//phyrexian mana
	PopulateIndex("WP", SDL_Rect{105*5, 105*4, 100, 100});
	PopulateIndex("UP", SDL_Rect{105*6, 105*4, 100, 100});
	PopulateIndex("BP", SDL_Rect{105*7, 105*4, 100, 100});
	PopulateIndex("RP", SDL_Rect{105*8, 105*4, 100, 100});
	PopulateIndex("GP", SDL_Rect{105*9, 105*4, 100, 100});
}

void ExampleScene::DestroyIndex() {
	for (auto it : manaIndex) {
		delete it.second;
	}
	manaIndex.clear();
}

void ExampleScene::RenderText(SDL_Renderer* renderer, std::string text, int x, int y) {
	//DOCS: quick and dirty
	SDL_Color color = {255, 255, 255, 255}; //white
	SDL_Rect rect = {x, y};

	//make the surface
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surface) {
		throw(std::runtime_error("Failed to create a TTF surface"));
	}

	//convert to texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_FreeSurface(surface);
		throw(std::runtime_error("Failed to create a TTF texture"));
	}

	//prevent warping
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	//render
	if (SDL_RenderCopy(renderer, texture, nullptr, &rect)) {
		std::cerr << "Failed to render a texture" << std::endl;
	}

	//cleanup
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void ExampleScene::RenderManaCost(SDL_Renderer* renderer, std::string str, int x, int y) {
	//hold the parsed codes in reverse order
	std::stack<std::string> manaCodes;

	//read the raw text
	char* rawText = (char*)(str.c_str());

	//count the symbols present
	int count = 0;
	for (char* it = rawText; *it; it++) {
		if (*it == '{') {
			count++;
		}
	}

	//read each symbol, and push it to the stack
	while(count) {
		while( *(rawText++) != '{'); //find the start of the next symbol

		//read the code
		char code[8];
		memset(code, 0, 8);
		sscanf(rawText, "%[^}]}", code);

		//push
		manaCodes.emplace(code);
		count--;
	}

	//finally, draw the correct symbols
	while(!manaCodes.empty()) {
		manaIndex[manaCodes.top()]->DrawTo(renderer, x + 12 * manaCodes.size(), y, .1, .1);
		manaCodes.pop();
	}
}