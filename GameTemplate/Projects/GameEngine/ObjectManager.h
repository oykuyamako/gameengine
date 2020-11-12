#pragma once

#include "Singleton.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Object.h"
#include <vector>


class ObjectManager : public Singleton<ObjectManager> {

	friend class Singleton<ObjectManager>;

private:
	ObjectManager() {};
	~ObjectManager() {};

public:
	int o_count = 0;
	//Object* objects = new Object[o_count];

	std::vector <Object*> objects;

	void addObject(Object*);
	void removeObject(Object*);
	void update();
};

