#pragma once
#include "Components.h"
#include "Actions.h"
#include "ECS.h"
#include "Inputs.h"
#include "ChangeInputMediator.h"

class Player  {
public:
	
	inline static Entity* CreatePlayer(Manager* manager, SDL_Renderer* renderer, ChangeInputMediator* mediator) {

		auto& player(manager->addEntity(pc));
		player.title = "player";
		IAction* action = new ActionPlayer(&player);
		SDL_Event* sdlEvent = new SDL_Event();
		InputManager* inputManager = new InputManager();
		player.tag = pc; 
		player.addComponent<Health>();
		player.addComponent<Transform>();
		player.getComponent<Transform>().getVector()->set(250,250);
		player.getComponent<Transform>().setSpeed(2);
		player.addComponent<InputPlayer>(sdlEvent, inputManager, mediator);
		player.addComponent<RectCollider>();
		player.getComponent<RectCollider>().instantiate(manager, action);
		player.getComponent<RectCollider>().setCollisionNorm(18, 60);
		player.addComponent<Texture>();
		player.getComponent<Texture>().instatiate(renderer, "Assets/dancer.png", 100, 100, 8, 100);
		player.getComponent<Texture>().setSizeCords(0, 0);
		player.addComponent<InputTennis>(sdlEvent, inputManager, manager, renderer, mediator);
		player.getComponent<InputTennis>().hide = true;
		player.addComponent<InputShoot>(sdlEvent, inputManager, manager, renderer, mediator);

		player.getComponent<InputShoot>().hide = true;
		player.addComponent<InputPacMan>(sdlEvent,inputManager, mediator);
		player.getComponent<InputPacMan>().hide = true;
		player.getComponent<InputPacMan>().init();
		player.isStatic = false;

		return &player;

	}

};