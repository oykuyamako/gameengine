#include "GameManager.h"
#include "EngineManager.h"

GameManager::GameManager() {
	backgr = Block(0, 0, 100, 100);
	up = Block(0, 0, 100, 100);
	down = Block(0, 430, 30, 30);
	left = Block(0, 0, 30, 30);
	right = Block(600, 0, 30, 30);
	c = Block(300, 200, 30, 30);
	end = Block(0, 0, 30, 30);
	d = Dot(300, 250, 0, 0, 20, 20, 10);

	blocks.push_back(new Block(30, 20, 30, 30));
	food.push_back(new Block(30, 20, 30, 30));
	
	timer = 0;
	route = 1000;
	randn = 0;

	ObjectManager::GetInstance().addObject(&backgr);
	ObjectManager::GetInstance().addObject(&up);
	ObjectManager::GetInstance().addObject(&down);
	ObjectManager::GetInstance().addObject(&left);
	ObjectManager::GetInstance().addObject(&right);
	ObjectManager::GetInstance().addObject(&c);
	ObjectManager::GetInstance().addObject(&end);
	ObjectManager::GetInstance().addObject(&d);

	for (auto t = blocks.begin(); t != blocks.end(); ++t) {
		ObjectManager::GetInstance().addObject((*t));
	}
	for (auto f = food.begin(); f != food.end(); ++f) {
		ObjectManager::GetInstance().addObject((*f));
	}

	startGame();
}

void GameManager::startGame() {

	SoundManager::GetInstance().LoadSound();

	if (!RenderManager::GetInstance().Init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (loadData()) {
			bool quit = false;

			SDL_Event e;

			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					d.handleEvent(e);
				}
				timer++;

				if (timer == 100) {
					double x = rand() / static_cast<double>(RAND_MAX + 1);
					randn = 0 + static_cast<int>(x * (4 - 0));
					std::cout << randn;
					timer = 0;
					if (randn == 0) {
						c.loadMedia("../../Media/arrowup.png");
					}else if (randn == 1) {
						c.loadMedia("../../Media/arrowleft.png");
					}else if (randn == 2) {
						c.loadMedia("../../Media/arrowdown.png");
					}else if (randn == 3) {
						c.loadMedia("../../Media/arrowright.png");
					}
				}
				for (auto t = blocks.begin(); t != blocks.end(); ++t) {
					(*t)->posY++;
					if ((*t)->posY > 500) {
						(*t)->close();
						int x = (rand() % 30 + 1) * 10;
						int y = rand() % 300 + 1;

						(*t) = new Block(x, y, 30, 30);
						ObjectManager::GetInstance().addObject(*t);
						(*t)->loadMedia("../../Media/bomb.png");
					}
					if (d.posX < (*t)->posX + (*t)->width &&
						d.posX + d.width >(*t)->posX&&
						d.posY < (*t)->posY + (*t)->height &&
						d.posY + d.height >(*t)->posY) {
						SoundManager::GetInstance().PlaySound(0);
						(*t)->close();
						int x = (rand() % 30 + 1) * 10;
						int y = rand() % 300 + 1;

						(*t) = new Block(x, y, 30, 30);
						ObjectManager::GetInstance().addObject(*t);
						(*t)->loadMedia("../../Media/bomb.png");
					}
				}
				for (auto f = food.begin(); f != food.end(); ++f) {
					(*f)->posY++;
					if ((*f)->posY > 500) {
						(*f)->close();
						int x = (rand() % 30 + 1) * 10;
						int y = rand() % 300 + 1;

						(*f) = new Block(x, y, 30, 30);
						ObjectManager::GetInstance().addObject(*f);
						(*f)->loadMedia("../../Media/life.png");
					}
					if (d.posX < (*f)->posX + (*f)->width &&
						d.posX + d.width >(*f)->posX&&
						d.posY < (*f)->posY + (*f)->height &&
						d.posY + d.height >(*f)->posY) {
						(*f)->close();
						int x = (rand() % 30 + 1) * 10;
						int y = rand() % 300 + 1;

						(*f) = new Block(x, y, 30, 30);
						ObjectManager::GetInstance().addObject(*f);
						(*f)->loadMedia("../../Media/life.png");
					}
				}
				InputManager::GetInstance().Update();

				ObjectManager::GetInstance().update();

				RenderManager::GetInstance().renderAll();
				if(randn==0){
					if (d.posY < 20) {
						printf("YYY");
						SoundManager::GetInstance().PlaySound(1);
					}
					else {
						printf("LOSER");
						route--;
					}
				}else if (randn == 1) {
					if (d.posX < 20 ) {
						printf("YYY");
						SoundManager::GetInstance().PlaySound(1);
					}
					else {
						printf("LOSER");
						route--;
					}
				}
				else if (randn == 2) {
					if (d.posY > 400) {
						printf("YYY");
						SoundManager::GetInstance().PlaySound(1);
					}
					else {
						printf("LOSER");
						route--;
					}
				}
				else if (randn == 3) {
					if (d.posX > 600) {
						printf("YYY");
						SoundManager::GetInstance().PlaySound(1);
					}
					else {
						printf("LOSER");
						route--;
					}
				}
				if (route == 0) {
					end.loadMedia("../../Media/peepee.jpg");
					d.close();
					up.close();
					down.close();
					left.close();
					right.close();
					c.close();
					//SoundManager::GetInstance().close();
				}
				
			}
		}
	}

	destroy();
}

bool GameManager::loadData() {
	if (!d.loadMedia("../../Media/pufff.png")) {
		printf("Failed to load media!\n");
		return false;
	}
	else if (!up.loadMedia("../../Media/up.bmp")) {
		printf("Failed to load media!\n");
		return false;
	}
	else if (!down.loadMedia("../../Media/down.bmp")) {
		printf("Failed to load media!\n");
		return false;
	}
	else if (!left.loadMedia("../../Media/left.bmp")) {
		printf("Failed to load media!\n");
		return false;
	}
	else if (!right.loadMedia("../../Media/right.bmp")) {
		printf("Failed to load media!\n");
		return false;
	}
	else if (!backgr.loadMedia("../../Media/abb.jpg")) {
		printf("Failed to load media!\n");
		return false;
	}
	else
		for (auto t = blocks.begin(); t != blocks.end(); ++t) {
			if (!(*t)->loadMedia("../../Media/bomb.png")) {
				return false;
			}
		}
	for (auto f = food.begin(); f != food.end(); ++f) {
		if (!(*f)->loadMedia("../../Media/bomb.png")) {
			return false;
		}
	}
		return true;
}

void GameManager::destroy() {
	d.close();
	backgr.close();
	up.close();
	down.close();
	left.close();
	right.close();
	c.close();
	end.close();
	for (auto t = blocks.begin(); t != blocks.end(); ++t) {
		(*t)->close();

		ObjectManager::GetInstance().removeObject((*t));
	}
	for (auto f = food.begin(); f != food.end(); ++f) {
		(*f)->close();

		ObjectManager::GetInstance().removeObject((*f));
	}

	ObjectManager::GetInstance().removeObject(&d);
	ObjectManager::GetInstance().removeObject(&backgr);
	ObjectManager::GetInstance().removeObject(&up);
	ObjectManager::GetInstance().removeObject(&down);
	ObjectManager::GetInstance().removeObject(&left);
	ObjectManager::GetInstance().removeObject(&right);
	ObjectManager::GetInstance().removeObject(&c);
	ObjectManager::GetInstance().removeObject(&end);
}

/*bool GameManager::checkCollision(Object obj1, Object obj2) {
	if (obj1.posX < obj2.posX + obj2.width &&
		obj1.posX + obj1.width > obj2.posX&&
		obj1.posY < obj2.posY + obj2.height &&
		obj1.posX + obj1.height > obj2.posY) {
		return true;
	}
	else
		return false;
}*/