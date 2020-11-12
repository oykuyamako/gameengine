#pragma once
#include "Object.h"

class Block : public Object {
public:
	Block()
		: Object() {};

	Block(int x, int y, int width, int height)
		: Object(x, y, width, height) {
	};

};

