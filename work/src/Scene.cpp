// Scene.cpp
#include "Scene.hpp"

void Scene::addObject(Object *obj) { objects.push_back(obj); }

void Scene::addLight(Light *light) { lights.push_back(light); }

std::vector<Object *> Scene::getObjects() { return objects; }

std::vector<Light *> Scene::getLights() { return lights; }

RayHit Scene::intersect(const Ray &ray) {
  RayHit closestHit;
  closestHit.hit = false;
  closestHit.m_distance = std::numeric_limits<float>::infinity();

  for (Object *obj : objects) {
    RayHit hit = obj->intersect(ray);
    if (hit.hit && hit.m_distance < closestHit.m_distance) {
      closestHit = hit;
    }
  }

  return closestHit;
}