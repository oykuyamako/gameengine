#include "EngineManager.h"

EngineManager::EngineManager() {
	InputManager::CreateSingleton();
	RenderManager::CreateSingleton();
	ObjectManager::CreateSingleton();
	SoundManager::CreateSingleton();
}

EngineManager::~EngineManager() {
	InputManager::DestroySingleton();
	RenderManager::DestroySingleton();
	ObjectManager::DestroySingleton();
	SoundManager::DestroySingleton();
}