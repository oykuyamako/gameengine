#include "Object.h"

Object::Object() {
	posX = 0;
	posY = 0;

	width = 0;
	height = 0;

	index = -1;
}

Object::Object(int x, int y, int width, int height) {
	posX = x;
	posY = y;

	this->width = width;
	this->height = height;

	index = -1;
}

void Object::update() {
}

bool Object::loadMedia(std::string path)
{
	bool success = true;

	if (!texture.loadFromFile(path)) {
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}

void Object::close() {
	texture.free();
}
