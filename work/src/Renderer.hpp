#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Camera.hpp"
#include "ILightTechnique.hpp"
#include "Scene.hpp"

class Renderer {
public:
  void initialize(Scene &scene);
  void renderFrame(Camera *camera);
  void shutdown();

  void setTechnique(ILightTechnique *technique);

private:
  ILightTechnique *currentTechnique;
  Scene *scene;
};

#endif // RENDERER_HPP
