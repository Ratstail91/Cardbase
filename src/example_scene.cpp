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

#include <iostream>
#include <stdexcept>

ExampleScene::ExampleScene() {
	//Testing this on ubuntu
	font = TTF_OpenFont(("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"), 12);

	if (!font) {
		throw(std::runtime_error("Failed to load font file"));
	}
}

ExampleScene::~ExampleScene() {
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
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect rect = {32, 32};

	SDL_Surface* surface = TTF_RenderText_Solid(font, "Foobar", color);

	if (!surface) {
		std::cerr << "Failed to create a TTF surface" << std::endl;
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {
		std::cerr << "Failed to create a TTF texture" << std::endl;
		SDL_FreeSurface(surface);
		return;
	}

	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	if (SDL_RenderCopy(renderer, texture, nullptr, &rect)) {
		std::cerr << "Failed to render a texture" << std::endl;
	}

	//cleanup
	SDL_FreeSurface(surface);
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
	}
}

void ExampleScene::KeyUp(SDL_KeyboardEvent const& event) {
	//
}
