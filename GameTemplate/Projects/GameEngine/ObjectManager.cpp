#include "ObjectManager.h"
#include <algorithm> 

void ObjectManager::addObject(Object* o) {
	o_count++;

	objects.push_back(o);

	o->index = o_count;
}

void ObjectManager::removeObject(Object* o) {
	//objects.erase(objects.begin + o->index - 1);

	for (auto t = ObjectManager::GetInstance().objects.begin(); t != ObjectManager::GetInstance().objects.end(); ++t) {
		if (*t == o) {
			objects.erase(t);
			break;
		}
	}
}

void ObjectManager::update() {
	for (auto t = ObjectManager::GetInstance().objects.begin(); t != ObjectManager::GetInstance().objects.end(); ++t) {
		(*t)->update();
	}
}
