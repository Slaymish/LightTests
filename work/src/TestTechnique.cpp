#include "TestTechnique.hpp"
#include <GLFW/glfw3.h>

void TestTechnique::initialize() {
  // Initialize resources ??
}

void TestTechnique::render(Scene &scene, Camera &camera) {
  camera.update();

  // projection matrix
  glm::mat4 proj = camera.getProjectionMatrix();

  // view
  glm::mat4 view = camera.getViewMatrix();

  // draw objects
  for (auto &object : scene.getObjects()) {
    object->draw(view, proj);
  }
}

void TestTechnique::cleanup() {
  // Clean up resources ??
}