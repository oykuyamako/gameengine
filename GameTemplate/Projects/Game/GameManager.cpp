#include "GameManager.h"
#include "EngineManager.h"

#include <SDL_thread.h>

#include <stdlib.h> 
#include <time.h>

GameManager::GameManager() {
	b = Block(0, 0, 0, 0);
	d = Dot(100, 100, 0, 0, 20, 20, 10);

	blocks.push_back(new Block(30, 20, 30, 30));


	ObjectManager::GetInstance().addObject(&b);
	ObjectManager::GetInstance().addObject(&d);

	for (auto t = blocks.begin(); t != blocks.end(); ++t) {
		ObjectManager::GetInstance().addObject((*t));
	}

	score = 0;

	startGame();
}

void GameManager::startGame() {

	if (!RenderManager::GetInstance().Init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (loadData()) {
			bool quit = false;

			SDL_Event e;

			RenderManager::GetInstance().mut = SDL_CreateMutex();

			int data = 101;

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					d.handleEvent(e);
				}
				//mainThread();
				SDL_Thread* mainID = SDL_CreateThread(mainThread, "LazyThread", (void*)data);

				int  threadReturnValue;
				//SDL_WaitThread(threadID, &threadReturnValue);
				//printf("\nThread returned value: %d", threadReturnValue);
			}
			SDL_DestroyMutex(RenderManager::GetInstance().mut);
		//SDL_Delay(5000);
		}
	}

	destroy();
}

bool GameManager::loadData() {
	if (!d.loadMedia("../../Media/food.png")) {
		printf("Failed to load media!\n");
		return false;
	}
	if (!b.loadMedia("../../Media/a1.jpg")) {
		printf("Failed to load media!\n");
		return false;
	}
	
	for (auto t = blocks.begin(); t != blocks.end(); ++t) {
		if (!(*t)->loadMedia("../../Media/coin.gif")) {
			return false;
		}
	}
	return true;
}

void GameManager::destroy() {
	d.close();
	b.close();

	for (auto t = blocks.begin(); t != blocks.end(); ++t) {
		(*t)->close();

		ObjectManager::GetInstance().removeObject((*t));
	}

	ObjectManager::GetInstance().removeObject(&d);
	ObjectManager::GetInstance().removeObject(&b);
}

bool GameManager::checkCollision(Object obj1, Object obj2) {
	if (obj1.posX < obj2.posX + obj2.width &&
		obj1.posX + obj1.width > obj2.posX&&
		obj1.posY < obj2.posY + obj2.height &&
		obj1.posX + obj1.height > obj2.posY) {
		return true;
	}
	else
		return false;
}

SDL_Surface* winCase(char* path)
{
	//Load splash image
	SDL_Surface* gHelloWorld = SDL_LoadBMP(path);
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
	}

	return gHelloWorld;
}

/*int GameManager::threadFunction(void* data)
{
	int cnt;
	for (cnt = 0; cnt < 10; ++cnt) {
		printf("\nThread counter: %d", cnt);
		SDL_Delay(50);
	}

	return cnt;
}*/

int mainThread(void* data) {

	if (SDL_mutexP(RenderManager::GetInstance().mut) == -1) {
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}
	/* Do stuff while mutex is locked */
	//printf("\nPhysic Thread counter: %d", cnt);

	printf("mainThread");
	InputManager::GetInstance().Update();

	srand(time(NULL));

	int x = (rand() % 30 + 1) * 10;
	int y = rand() % 300 + 1;

	for (auto t = blocks.begin(); t != blocks.end(); ++t) {
		if (d.posX < (*t)->posX + (*t)->width &&
			d.posX + d.width >(*t)->posX&&
			d.posY < (*t)->posY + (*t)->height &&
			d.posY + d.height >(*t)->posY) {

			(*t)->close();
			score += 10;
			if (score == 50) {
				scoreboard.push_back(new Object((scoreboard.size() * 50), 0, 20, 20));
				ObjectManager::GetInstance().addObject((scoreboard.back()));

				scoreboard.back()->loadMedia("../../Media/star.bmp");
				score = 0;
			}
			if (scoreboard.size() > 12) {

				SDL_Surface* gHelloWorld = winCase("../../Media/won.bmp");
				SDL_Surface* gScreenSurface = SDL_GetWindowSurface(RenderManager::GetInstance().GetWindow());

				SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

				SDL_UpdateWindowSurface(RenderManager::GetInstance().GetWindow());

				break;
			}

			(*t) = new Block(x, y, 30, 30);
			ObjectManager::GetInstance().addObject(*t);
			(*t)->loadMedia("../../Media/coin.gif");
		}
	}

	ObjectManager::GetInstance().update();

	SDL_Thread* threadID = SDL_CreateThread(RenderManager::threadFunction, "LazyThread", (void*)data);

	//SDL_Delay(2000);

	if (SDL_mutexV(RenderManager::GetInstance().mut) == -1) {
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}

	//SDL_Delay(1000);

	return 0;
}