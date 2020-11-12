#pragma once

#include "Object.h"

class MovingObject : public Object {
public:
	int velocity;
	int velX, velY;

	MovingObject()
		: Object() {
		this->velocity = 0;
		this->velX = 0;
		this->velY = 0;
	}

	MovingObject(int x, int y, int velX, int velY, int width, int height, int velocity)
		: Object(x, y, width, height) {
		this->velocity = velocity;
		this->velX = velX;
		this->velY = velY;
	}

	void move();
	void handleEvent(SDL_Event& e);
};

