#include "RenderManager.h"
#include "ObjectManager.h"
#include <SDL_thread.h>

/*****************************************************************************/

RenderManager::RenderManager(void)
{
}

/*****************************************************************************/

RenderManager::~RenderManager(void)
{
	//Destroy window	
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/*****************************************************************************/

bool RenderManager::Init(void)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					const char* error = IMG_GetError();
					printf("SDL_image could not initialize! SDL_image Error: %s\n", error);
					success = false;
				}
			}
		}
	}

	mut = SDL_CreateMutex();

	return success;
}

/*****************************************************************************/

void RenderManager::Update(void)
{
}

void RenderManager::renderAll() {
	int data = 101;
	//SDL_Thread* threadID = SDL_CreateThread(RenderManager::threadFunction, "LazyThread", (void*)data);

	//SDL_WaitThread( threadID, NULL );
	int  threadReturnValue;
	//SDL_WaitThread(threadID, &threadReturnValue);
	//printf("\nThread returned value: %d", threadReturnValue);

	//SDL_Delay(5000);
}

int RenderManager::threadFunction(void* data)
{
	if (SDL_mutexP(RenderManager::GetInstance().mut) == -1) {
		fprintf(stderr, "Couldn't lock mutex\n");
		exit(-1);
	}

		printf("renderThread");

		SDL_Rect* clip = NULL;
		double angle = 0.0;
		SDL_Point* center = NULL;
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		SDL_SetRenderDrawColor(RenderManager::GetInstance().GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(RenderManager::GetInstance().GetRenderer());
		//Print incoming data
		//printf("Running thread with value = %d\n", (int)data);

		for (auto t = ObjectManager::GetInstance().objects.begin(); t != ObjectManager::GetInstance().objects.end(); ++t) {

			SDL_Rect temp = { (*t)->posX, (*t)->posY, (*t)->texture.mWidth, (*t)->texture.mHeight };

			if (clip != NULL)
			{
				temp.w = clip->w;
				temp.h = clip->h;
			}

			SDL_RenderCopyEx(RenderManager::GetInstance().GetRenderer(), (*t)->texture.mTexture, clip, &temp, angle, center, flip);
		}

		SDL_RenderPresent(RenderManager::GetInstance().GetRenderer());
		//SDL_Delay(2000);

	if (SDL_mutexV(RenderManager::GetInstance().mut) == -1) {
		fprintf(stderr, "Couldn't unlock mutex\n");
		exit(-1);
	}

	//SDL_Delay(1000);
	return 0;
}

/*****************************************************************************/

/*****************************************************************************/
