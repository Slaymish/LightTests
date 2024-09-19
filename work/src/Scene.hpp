#ifndef SCENE_HPP
#define SCENE_HPP

#include "Light.hpp"
#include "Object.hpp"
#include "RayHit.hpp"
#include "ray.hpp"
#include <vector>

class Scene {
public:
  void addLight(Light *light);
  void addObject(Object *obj);
  std::vector<Object *> getObjects();
  std::vector<Light *> getLights();

  RayHit intersect(const Ray &ray);

private:
  std::vector<Object *> objects;
  std::vector<Light *> lights;
};

#endif // SCENE_HPP
