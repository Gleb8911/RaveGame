#pragma once
#include "ECS.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Transform.h"


#define STD_W 110
#define STD_H 128
#define SCALE 1

class Texture : public Component {
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect inGameTexRect;
	SDL_Rect inRawTexRect;

	bool animated = false;
	int speed = 100;
	int frames = 8;
	
public:
	void setPosSize(int w, int h) {
		this->inGameTexRect.h = h;
		this->inGameTexRect.w = w;
	}

	void setSizeSize(int w, int h) {
		this->inRawTexRect.h = h;
		this->inRawTexRect.w = w;
	}
	void setPosCords(int x, int y) {
		this->inGameTexRect.x = x;
		this->inGameTexRect.y = y;
	}

	void setSizeCords(int x, int y) {
		this->inRawTexRect.x = x;
		this->inRawTexRect.y = y;
	}


	void instatiate(SDL_Renderer* renderer, const char* texPass, int height, int width) {
		this->renderer = renderer;

		this->texture = TextureManager::loadTexture(texPass, renderer);
		if (this->entity->hasComponent<Transform>()) {
			inGameTexRect.x = this->entity->getComponent<Transform>().getVector()->getX();
			inGameTexRect.y = this->entity->getComponent<Transform>().getVector()->getY();
			inGameTexRect.h = STD_H * SCALE;
			inGameTexRect.w = STD_W * SCALE;
		}

		inRawTexRect.h = STD_H;
		inRawTexRect.w = STD_W;
		inRawTexRect.x = 0;
		inRawTexRect.y = 0;


	}
	void instatiate(SDL_Renderer* renderer, const char* texPass, int height, int width, int nFrames, int speed) {
		this->renderer = renderer;
		this->speed = speed;
		animated = true;
		this->frames = nFrames;
		this->texture = TextureManager::loadTexture(texPass, renderer);
		if (this->entity->hasComponent<Transform>()) {
			inGameTexRect.x = this->entity->getComponent<Transform>().getVector()->getX();
			inGameTexRect.y = this->entity->getComponent<Transform>().getVector()->getY();
			inGameTexRect.h = STD_H * SCALE;
			inGameTexRect.w = STD_W * SCALE;
		}

		inRawTexRect.h = STD_H;
		inRawTexRect.w = STD_W;
		inRawTexRect.x = 0;
		inRawTexRect.y = STD_H * 7;


	}
	Texture() {
	}
	~Texture() {
	
	}

	void init() override{
		
	}

	void update() override {
		if (animated) {
			inRawTexRect.x = inRawTexRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		if (!(this->hide)) {
			inGameTexRect.x = (this->entity->getComponent<Transform>().getVector()->getX() - inGameTexRect.w / 2);
			inGameTexRect.y = (this->entity->getComponent<Transform>().getVector()->getY() - inGameTexRect.h / 2);
		}
	}

	void draw() {
		SDL_RenderCopy(this->renderer, this->texture, &this->inRawTexRect, &this->inGameTexRect);
	}
};