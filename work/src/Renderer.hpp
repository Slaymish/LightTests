#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Camera.hpp"
#include "ILightTechnique.hpp"
#include "Scene.hpp"

class Renderer {
public:
  void initialize();
  void renderFrame(Scene &scene, Camera &camera);
  void shutdown();

  void setTechnique(ILightTechnique *technique);

private:
	ILightTechnique* currentTechnique;
};

#endif // RENDERER_HPP
