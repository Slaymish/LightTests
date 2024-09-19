#include "TestTechnique.hpp"
#include <GLFW/glfw3.h>

void TestTechnique::initialize(Scene &scene) {
  // Initialize resources ??
  this->scene = &scene;
}

void TestTechnique::render(Camera *camera) {
  // draw objects
  for (auto &object : scene->getObjects()) {
    object->draw(camera);
  }
}

void TestTechnique::cleanup() {
  // Clean up resources ??
}