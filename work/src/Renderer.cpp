// Renderer.cpp
#include "Renderer.hpp"
#include <iostream>

void Renderer::initialize() {
  if (currentTechnique) {
    currentTechnique->initialize();
  }
}

void Renderer::renderFrame(Scene &scene, Camera &camera) {
  if (currentTechnique) {
    currentTechnique->render(scene, camera);
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
    currentTechnique->initialize();
  }
}
