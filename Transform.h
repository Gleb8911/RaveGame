#pragma once
#include "ECS.h"
#include "Vector2D.h"


#define SPEED 1
#define KOEF 1
class Transform : public Component {
public:

	Transform() {
		this->position = new Vector2D();
		this->moveVector = new Vector2D();
	}
	Transform(float x, float y) {
		this->position = new Vector2D(x, y);
		this->moveVector = new Vector2D();
	}
	~Transform() {
		delete(position);
	}
//Start of COmponents override
	void init() override {
	}
	void update() override {
		if (!(this->hide)) {
			move();
		}
	}

//End of Components override
	void move() {
		this->moveVector->normalize();
		this->position->set( this->position->getX() + this->moveVector->getX() * this->speed, this->position->getY() + this->moveVector->getY() * this->speed);
		this->speed = (this->speed < 0.001) ? 0 : (this->speed * dumpingKoef);
	}
	
	void setSpeed(float speed) {
		this->speed = speed;
	}
	float getSpeed() {
		return this->speed;
	}
	Vector2D* getVector() {
		return position;
	}
	void setVector(Vector2D* position) {
		this->position = position;
	}
	Vector2D* getMoveVector() {

		return this->moveVector;
	}
	void setMoveVector(Vector2D* moveVector) {
		this->moveVector = moveVector;
	}

	void SetDumpingKoef(float koef) {
		this->dumpingKoef = koef;
	}

private:
	Vector2D* moveVector;
	Vector2D* position;
	float speed = SPEED;
	float dumpingKoef = KOEF;
};
