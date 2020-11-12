#pragma once

#include "MovingObject.h"

class Dot : public MovingObject {

public:
	Dot()
		: MovingObject() {
	}

	Dot(int x, int y, int velX, int velY, int width, int height, int velocity)
		: MovingObject(x, y, velX, velY, width, height, velocity) {
	}

	void update();
};