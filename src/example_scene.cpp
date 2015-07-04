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
	masterManaSheet.Load(GetRenderer(), "rsc/Mana.png");
	CreateIndex();

	//read and store the .json file
	std::ifstream is("rsc/AllCards.json");

	if (!is.is_open()) {
		throw(std::runtime_error("Failed to open the json file for reading"));
	}
	cardData << is;
	is.close();

	//DEBUG: output specific cards
//	std::cout << cardData["Aboroth"]["text"] << std::endl;
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
	SDL_Texture* texture = nullptr;
	SDL_Rect src, dest;

	int line = 0;

	for (auto& it : cardData) {
		//render name
		texture = RenderPlainText(renderer, it["name"]);

		//get the stats for name, then draw
		src = SDL_Rect{0, 0};
		SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
		dest = SDL_Rect{32, 32 + 16 * line, src.w, src.h};
		SDL_RenderCopy(renderer, texture, &src, &dest);

		//cleanup
		SDL_DestroyTexture(texture);
		texture = nullptr;

		//render mana (if applicable)
		try {
			if (it["manaCost"].type() != nlohmann::json::value_t::null) {
				texture = RenderManaCost(renderer, it["manaCost"]);

				//get the stats for manaCost, then draw
				src = SDL_Rect{0, 0};
				SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
				dest = SDL_Rect{300, 32 + 16 * line, src.w, src.h};
				SDL_RenderCopy(renderer, texture, &src, &dest);

				//cleanup
				SDL_DestroyTexture(texture);
				texture = nullptr;
			}
		}
		catch(std::exception& e) {
			//find what cards break the system
			std::ostringstream msg;
			msg << e.what() << "; " << it["name"] << "; manaCost: " << it["manaCost"];
			throw(std::runtime_error(msg.str()));
		}

		//render text (if applicable)
		try {
			if (it["text"].type() != nlohmann::json::value_t::null) {
				texture = RenderPlainText(renderer, it["text"]);

				//get the stats for text, then draw
				src = SDL_Rect{0, 0};
				SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
				dest = SDL_Rect{400, 32 + 16 * line, src.w, src.h};
				SDL_RenderCopy(renderer, texture, &src, &dest);

				//cleanup
				SDL_DestroyTexture(texture);
				texture = nullptr;
			}
		}
		catch(std::exception& e) {
			//find what cards break the system
			std::ostringstream msg;
			msg << e.what() << "; " << it["name"] << "; text: " << it["text"];
			throw(std::runtime_error(msg.str()));
		}

		//DEBUG: emergency cap
		if (line++ >= 50) break;
	}

	//DEBUG: draw the framerate & number of cards
	frameRate.Calculate();
	char debug[64];
	sprintf(debug, "FPS: %d, Cards indexed: %lu", frameRate.GetFrameRate(), cardData.size());
	texture = RenderPlainText(renderer, debug);
	src = SDL_Rect{0, 0};
	SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
	dest = SDL_Rect{0, 0, src.w, src.h};
	SDL_RenderCopy(renderer, texture, &src, &dest);
	SDL_DestroyTexture(texture);
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
		case SDLK_SPACE: {
			nlohmann::json::iterator it = cardData.begin();
			for (int i = 0; i < 40; i++) it++;
			cardData.erase(cardData.begin(), it);
		}
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
	PopulateIndex("W/P", SDL_Rect{105*5, 105*4, 100, 100});
	PopulateIndex("U/P", SDL_Rect{105*6, 105*4, 100, 100});
	PopulateIndex("B/P", SDL_Rect{105*7, 105*4, 100, 100});
	PopulateIndex("R/P", SDL_Rect{105*8, 105*4, 100, 100});
	PopulateIndex("G/P", SDL_Rect{105*9, 105*4, 100, 100});

	//oddball mana
	PopulateIndex("1000000", SDL_Rect{105*0, 105*6, 512, 100});
	//100~
	PopulateIndex("hw", SDL_Rect{831, 105*6, 50, 100});
//	PopulateIndex("hr", SDL_Rect{886, 105*6, 50, 100});
}

void ExampleScene::DestroyIndex() {
	for (auto it : manaIndex) {
		delete it.second;
	}
	manaIndex.clear();
}

SDL_Texture* ExampleScene::RenderPlainText(SDL_Renderer* renderer, std::string text) {
	//DOCS: quick and dirty
	SDL_Color color = {255, 255, 255, 255}; //white

	//make the surface (from SDL_ttf)
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

	//cleanup
	SDL_FreeSurface(surface);

	//NOTE: free the texture yourself
	return texture;
}

SDL_Texture* ExampleScene::RenderManaCost(SDL_Renderer* renderer, std::string text) {
	//handle oddball manacosts
	bool oddball = false;

	//hold the parsed codes in reverse order
	std::stack<std::string> manaCodes;

	//get the raw text
	char* rawText = (char*)(text.c_str());

	//count the symbols present
	int count = 0;
	for (char* it = rawText; *it; it++) {
		//assume that all symbols start with '{'
		if (*it == '{') {
			count++;
		}
	}

	//read each symbol, and push it to the stack
	char code[8];
	while(count--) {
		while(*(rawText++) != '{'); //find the start of the next symbol

		//read the code
		memset(code, 0, 8);
		sscanf(rawText, "%[^}]", code);

		//push
		manaCodes.emplace(code);

		//Gleemax
		if (!strcmp(code, "1000000")) {
			oddball = true;
		}
	}

	//make a new texture to return
	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		oddball ? 512 : 12 * manaCodes.size(), //use 12px sizes to match the text, or 512 for oddball cards
		12);

	//draw to the texture
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderClear(renderer);

	while(!manaCodes.empty()) {
		manaIndex.at(manaCodes.top())->DrawTo(renderer, 1 + 12 * (manaCodes.size() -1), 1, .1, .1);
		manaCodes.pop();
	}

	SDL_SetRenderTarget(renderer, nullptr);

	//return this texture
	return texture;
}
