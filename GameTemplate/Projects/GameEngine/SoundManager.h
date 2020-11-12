#pragma once

#include "Singleton.h"
#include "SDL.h"
#include "SoundManager.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include <vector>


class SoundManager :public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;
	
private:

	SoundManager() {};
	~SoundManager() {};

public:

	void Update(void);
	Mix_Chunk* sounds [2];

	bool LoadSound();
	void PlaySound(int i);
	void PlayMusic(int i);
	void close();
};

