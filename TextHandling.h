#pragma once
#include "SDL_ttf.h"
#include <iostream>
#include "LevelManager.h"
#include <string>

class Text {
private:
	TTF_Font* font;
	SDL_Texture* textTexture;
	SDL_Color color;
	SDL_Renderer* renderer;
	SDL_Rect* rect;
	LevelManager* levelManager;
	int prevScore;
public:

	Text(SDL_Renderer* renderer, LevelManager* levelManager) {
		if (TTF_Init() < 0) {
			std::cout << "ERROR in TTF_Init " << std::endl;
		}
		font = TTF_OpenFont("Assets/arcadeFont.ttf", 60);
		//color = { 144 , 77 , 255, 255 };
		this->levelManager = levelManager;
	}

	void createSetSurface(const char* text) {
		SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
		textTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		SDL_Rect textRect;
		textRect.x = textRect.y = 200;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		this->rect = &textRect;
	}
	void setPrevLevel(int l) {
		prevScore = l;
	}
	void update() {
		if (prevScore != levelManager->getScore()) {
			prevScore = levelManager->getScore();
			std::string sScore = std::to_string(prevScore);
			createSetSurface(sScore.c_str());
		}
	}
	void draw() {
		SDL_RenderCopy(this->renderer, this->textTexture, NULL, this->rect);
	}
};