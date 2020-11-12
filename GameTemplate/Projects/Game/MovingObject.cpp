#include "MovingObject.h"
#include "SoundManager.h"

void MovingObject::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY -= velocity; break;
		case SDLK_DOWN: velY += velocity; break;
		case SDLK_LEFT: velX -= velocity; break;
		case SDLK_RIGHT: velX += velocity; break;
		case SDLK_9: SoundManager::GetInstance().PlayMusic(0); break;
		case SDLK_0: SoundManager::GetInstance().PlayMusic(1); break;
		}
	}

	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: velY += velocity; break;
		case SDLK_DOWN: velY -= velocity; break;
		case SDLK_LEFT: velX += velocity; break;
		case SDLK_RIGHT: velX -= velocity; break;
		}
	}
}

void MovingObject::move() {
	velX = 0;
	velY = 0;
	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_UP)) {
		
		velY -= velocity;
	}
	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_DOWN)) {
	
		velY += velocity;
	}
	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_LEFT)) {
		velX -= velocity;
	}
	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_RIGHT)) {
		velX += velocity;
	}

	posX += velX;

	if ((posX < 0) || (posX + width > RenderManager::SCREEN_WIDTH)) {
		posX -= velX;
	}

	posY += velY;

	if ((posY < 0) || (posY + height > RenderManager::SCREEN_HEIGHT)) {
		posY -= velY;
	}
}