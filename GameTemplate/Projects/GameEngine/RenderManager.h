#pragma once

#include "Singleton.h"
#include "SDL.h"
#include "SDL_image.h"

/**
Render Manager class
*/
class RenderManager :public Singleton<RenderManager>
{
	/*****************************************************************************/
	friend class Singleton<RenderManager>;
	/*****************************************************************************/

public:
	//Screen dimension constants
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

private:
	//The window we'll be rendering to
	SDL_Window* mWindow = NULL;

	//The window renderer
	SDL_Renderer* mRenderer = NULL;



	// Private constructor to avoid more than one instance
	RenderManager();
	~RenderManager();

	/*****************************************************************************/

public:

	bool Init(void);

	void Update(void);

	SDL_Window* GetWindow(void) { return mWindow; }

	SDL_Renderer* GetRenderer(void) { return mRenderer; }

	void renderAll();

	static int threadFunction(void* data);

	SDL_mutex* mut;

	/****************************void* data*************************************************/

};