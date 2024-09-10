// Scene.cpp
#include "Scene.hpp"

void Scene::addObject(Object *obj) { objects.push_back(obj); }

void Scene::addLight(Light *light) { lights.push_back(light); }

std::vector<Object *> Scene::getObjects() { return objects; }

std::vector<Light *> Scene::getLights() { return lights; }
