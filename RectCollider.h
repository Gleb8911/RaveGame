#pragma once
#include "ECS.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Actions.h"

class RectCollider : public Component {
private:
	Manager* manager;
	//IAction* actionInstance;
	Vector2D* moveVector;
	int collisionNormX = 25;
	int collisionNormY = 25;
	bool debugBool = true;

	void checkNotColliding(RectCollider* rectCollider) {
		//if (this->entity->tag == pc) {
		if (this->entity != rectCollider->entity) {			
			moveVector = this->entity->getComponent<Transform>().getVector()->minusVector(rectCollider->entity->getComponent<Transform>().getVector());
			if (moveVector->getX() * moveVector->getX() <=
				(this->collisionNormX + rectCollider->collisionNormX) *
				(this->collisionNormX + rectCollider->collisionNormX) && moveVector->getY() *
				moveVector->getY() <= (this->collisionNormY + rectCollider->collisionNormY) *
				(this->collisionNormY + rectCollider->collisionNormY)) {

				this->entity->collisionState = colliding;
				rectCollider->entity->collisionState = colliding;
			}
		}
		//}
		//else {
			//return 2;
		//}
	}

	void checkColliding(RectCollider* rectCollider) {		// the Trigger colider checks the colision with the nonTrigger
		moveVector = this->entity->getComponent<Transform>().getVector()->minusVector(rectCollider->entity->getComponent<Transform>().getVector());
		if (moveVector->getX() * moveVector->getX() >=
			(this->collisionNormX + rectCollider->collisionNormX) *
				(this->collisionNormX + rectCollider->collisionNormX) || moveVector->getY() *
					moveVector->getY() >= (this->collisionNormY + rectCollider->collisionNormY) *
						(this->collisionNormY + rectCollider->collisionNormY)) {

			this->entity->collisionState = wasColliding;
			rectCollider->entity->collisionState = wasColliding;
			}
	}
public:
	IAction* actionInstance;

	int* getCollisionNorm() {
		int* WH = new int[2];
		WH[0] = collisionNormX;
		WH[1] = collisionNormY;
		return WH;
	}

	Vector2D* getSetMoveVector(RectCollider* rectCollider) {
		this->moveVector = this->entity->getComponent<Transform>().getVector()->minusVector(rectCollider->entity->getComponent<Transform>().getVector());
		return this->moveVector;
	}
	void setCollisionNorm(int w, int h) {
		this->collisionNormX = w;
		this->collisionNormY = h;
	}
	void update() override {
		if (!(this->hide)) {
			if (!this->entity->isStatic) {
				this->collisionAction();
			}
		}
	}
	void init() override {

	}

	void collisionAction() {
		this->debugBool = false;
		for (int j = 0; j < this->manager->returnSizeEntities(); j++) {
			if (this->manager->getEntityByiD(j)->hasComponent<RectCollider>()) {
				collisionStateCheck(&(this->manager->getEntityByiD(j)->getComponent<RectCollider>()));
			}
		}
		if (!debugBool) {
			this->entity->collisionState = notColliding;
		}
	}


void collisionStateCheck(RectCollider* rectCollider) {
	switch (this->entity->collisionState) {
		case(notColliding):
			if (rectCollider->entity->collisionState == notColliding && (this->entity != rectCollider->entity)) {
				checkNotColliding(rectCollider);
				debugBool = true;
			}
			
			break;
		case(colliding):
			if (rectCollider->entity->collisionState == colliding && (this->entity != rectCollider->entity)) {
				checkColliding(rectCollider);
				if (!rectCollider->entity->isNotMovable)this->actionInstance->actionIn(rectCollider->entity, rectCollider->getSetMoveVector(this), this->getCollisionNorm());
				rectCollider->actionInstance->actionIn(this->entity, this->moveVector, rectCollider->getCollisionNorm());
				debugBool = true;
			}
			break;
		case(wasColliding):
			if (rectCollider->entity->collisionState == wasColliding && (this->entity != rectCollider->entity)) {
				this->entity->collisionState = notColliding;
				rectCollider->entity->collisionState = notColliding;
				if (!rectCollider->entity->isNotMovable)rectCollider->actionInstance->actionOut(this->entity);
				this->actionInstance->actionOut(rectCollider->entity);
				debugBool = true;
			}
			break;
		default:
			break;
	}
}


	void instantiate(Manager* manager, IAction* action) {

		this->actionInstance = action;
		this->manager = manager;
	}
};