// Renderer.cpp
#include "Renderer.hpp"
#include <iostream>

void Renderer::initialize(Scene &scene) {
  this->scene = &scene;
  if (currentTechnique) {
    currentTechnique->initialize(scene);
  }
}

void Renderer::renderFrame(Camera *camera) {
  if (currentTechnique) {
    currentTechnique->render(camera);
  } else {
    std::cerr << "No technique set for rendering" << std::endl;
  }
}

void Renderer::shutdown() {
  if (currentTechnique) {
    currentTechnique->cleanup();
  }
}

void Renderer::setTechnique(ILightTechnique *technique) {
  currentTechnique = technique;
  if (currentTechnique) {
    currentTechnique->initialize(*scene);
  }
}
