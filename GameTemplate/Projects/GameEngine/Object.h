#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "InputManager.h"
#include "RenderManager.h"

#include "Texture.h";

class Object {
public:
	int width;
	int height;

	int posX, posY;

	int index;

	LTexture texture;

	Object();
	Object(int x, int y, int width, int height);

	virtual void update();

	bool loadMedia(std::string path);

	void close();
};

