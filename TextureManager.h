#pragma once
#include "SDL_image.h"
#include "SDL.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* texture, SDL_Renderer* renderer) {
		SDL_Surface* tmpSurface = IMG_Load(texture);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
		return tex;
	}
};