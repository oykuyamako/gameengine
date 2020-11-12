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

	//int threadFunction(void* data);

	bool checkCollision(Object, Object);
};

static int mainThread(void* data);

static Dot d;
static Block b;
static std::vector <Block*> blocks;

static std::vector <Object*> scoreboard;
static int score;

static SDL_Surface* winCase(char*);

