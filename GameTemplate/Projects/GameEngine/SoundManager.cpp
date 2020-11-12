#include "SoundManager.h"

Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* gSound1 = NULL;
Mix_Chunk* gSound2 = NULL;
void SoundManager::Update(void)
{


}
/*****************************************************************************/

void SoundManager::close()
{
	
	//Free the music
	if (gMusic != NULL) {
		Mix_FreeMusic(gMusic);
		gMusic = NULL;
	}

	//Free sounds
	Mix_FreeChunk(gSound1);
	Mix_FreeChunk(gSound2);
	gSound1 = NULL;
	gSound2 = NULL;


	//Quit SDL subsystems
	Mix_Quit();


}

bool SoundManager::LoadSound()
{
	bool success = true;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gMusic = Mix_LoadMUS("../../Media/mrk.mp3");

	if (gMusic == NULL) {
		printf("Failed to load beat music!! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gSound1 = Mix_LoadWAV("../../Media/high.wav"); 
	sounds[0] = gSound1;


	if (sounds[0] == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gSound2 = Mix_LoadWAV("../../Media/low.wav");
	sounds[1] = gSound2;


	if (sounds[1] == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	

	return success;
}

void SoundManager::PlaySound(int i) {
	
	bool quit = false;
	//While application is running

	Mix_PlayChannel(-1, sounds[i], 0);
	/*while (!quit) {
		if (Mix_PlayingMusic() == 0) {
			//Play the music
			Mix_PlayMusic(sounds[i], -1);
		}
	}*/
}

void SoundManager::PlayMusic(int i) {

	if (i == 0) {
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(gMusic, -1);
		}
		//If music is being played
		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1)
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				//Pause the music
				Mix_PauseMusic();
			}
		}
	}
	else if (i == 1) {

		Mix_HaltMusic();
	}
}
