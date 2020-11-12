#pragma once

#include "EngineManager.h"
#include "GameManager.h"

int main(int argc, char* args[])
{
	EngineManager::CreateSingleton();
	
	GameManager g = GameManager();

	EngineManager::DestroySingleton();

	return 0;
}