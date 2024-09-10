#include "TestTechnique.hpp"
#include <GLFW/glfw3.h>

void TestTechnique::initialize() {
  // Initialize resources ??
}

void TestTechnique::render(Scene &scene, Camera &camera) {
  // Just get something on the screen

  // Clear the screen
  glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TestTechnique::cleanup() {
  // Clean up resources ??
}