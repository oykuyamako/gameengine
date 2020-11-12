#pragma once

#include "Singleton.h"
#include "SDL.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"

#include <vector>

class EngineManager : public Singleton<EngineManager> {

	friend class Singleton<EngineManager>;
	
private:
	EngineManager();
	~EngineManager();

public:
	//std::vector<Singleton> Managers;

};

