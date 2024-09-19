// ThreePassTechnique.cpp
#include "ThreePassTechnique.hpp"

void ThreePassTechnique::initialize(Scene &scene) {
  // Initialize resources for the Three Pass technique (e.g., shaders, buffers)
  this->scene = &scene;
}

void ThreePassTechnique::render(Camera *camera) {
  // Perform the Three-Pass rendering (e.g., G-buffer pass, light pass, final
  // composition)
}

void ThreePassTechnique::cleanup() {
  // Clean up resources for the Three-Pass technique
}
