#pragma once
#include "Vector2D.h"

class Move {
public:
	static void left(Vector2D* moveVector) {
		moveVector->setX(-1);
	}
	static void right(Vector2D* moveVector){
		moveVector->setX(1);
	}
	static void up(Vector2D* moveVector) {
		moveVector->setY(-1);
	}
	static void down(Vector2D* moveVector) {
		moveVector->setY(1);
	}
};