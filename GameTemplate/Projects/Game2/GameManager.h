#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "EngineManager.h"

#include "Texture.h"
#include "Object.h"
#include "Dot.h"
#include "Block.h"

class GameManager {
public:
	GameManager();

	void startGame();
	bool loadData();
	void update();
	void destroy();

	//bool checkCollision(Object, Object);

	Dot d;

	Block backgr;
	Block up;
	Block down;
	Block left;
	Block right;
	Block c;
	Block end;

	std::vector <Block*> blocks;
	std::vector <Block*> food;

	int timer;
	int route;
	int randn;

};

