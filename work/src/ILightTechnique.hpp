#ifndef ILIGHTTECHNIQUE_HPP
#define ILIGHTTECHNIQUE_HPP

#include "Camera.hpp"
#include "Scene.hpp"

class ILightTechnique {
public:
  virtual void initialize() = 0;
  virtual void render(Scene &scene, Camera &camera) = 0;
  virtual void cleanup() = 0;
  virtual ~ILightTechnique() = default;
};

#endif // ILIGHTTECHNIQUE_HPP
