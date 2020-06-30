#pragma once
#include <math.h> // need the sqr() function -- fix in future with own func
class Vector2D {
public:
	Vector2D(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2D() {
		this->x = 0;
		this->y = 0;
	}

	Vector2D operator + (Vector2D b) {
		return Vector2D(this->x + b.x, this->y + b.y);
	}
	Vector2D operator - (Vector2D b) {
		return Vector2D(this->x - b.x, this->y - b.y);
	}
	Vector2D operator - (float i) {
		return Vector2D(this->x - i, this->y - i);
	}
	Vector2D operator * (float b) {

		return Vector2D(this->x * b, this->y * b);
	}
	bool operator == (const Vector2D& second) {
		if ((this->x == second.x) && (this->y == second.y)) {
			return true;
		}
		else
			return false;
	}

	float getX() {
		return this->x;
	}
	float getY() {
		return this->y;
	}
	void setX(float x) {
		this->x = x;
	}
	void setY(float y) {
		this->y = y;
	}
	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2D* minusVector(Vector2D* vector) {
		Vector2D* newVector = new Vector2D(this->getX() - vector->getX(), this->getY() - vector->getY());
		return newVector;
	}
	Vector2D* plusVector(Vector2D* vector) {
		return &(Vector2D(this->getX() + vector->getX(), this->getY() + vector->getY()));
	}
	float getLength() {
		return sqrtf(this->x * this->x + this->y * this->y);
	}
	void normalize() {
		if (this->getLength() != 0) {
			this->x *= 1 / this->getLength();
			this->y *= 1 / this->getLength();
		}
		else {
			this->x = 0;
			this->y = 0;
		}
	}
	void setOposite() {
		this->x = -this->x;
		this->y = -this->y;
	}
	static void coutVector(Vector2D* moveVector) {
		std::cout << moveVector->getX() << '\t' << moveVector->getY() << std::endl;
	}
private:
	float x;
	float y;
};
