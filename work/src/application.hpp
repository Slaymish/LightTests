
#pragma once

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// project
#include "Renderer.hpp"
#include "Scene.hpp"
#include "cgra/cgra_mesh.hpp"
#include "opengl.hpp"

// Basic model that holds the shader, mesh and transform for drawing.
// Can be copied and modified for adding in extra information for drawing
// including textures for texture mapping etc.
struct basic_model {
  GLuint shader = 0;
  cgra::gl_mesh mesh;
  glm::vec3 color{0.7};
  glm::mat4 modelTransform{1.0};
  GLuint texture;

  void draw(const glm::mat4 &view, const glm::mat4 proj);
};

// Main application class
//
class Application {
private:
  // window
  GLFWwindow *m_window;

  // time-keeping
  float m_dt_last;
  std::chrono::steady_clock::time_point m_time_last =
      std::chrono::steady_clock::now();

  // drawing flags
  bool m_showWireframe = false;

  Scene m_scene;
  std::unique_ptr<Camera> m_camera = nullptr;
  std::unique_ptr<Renderer> m_renderer = nullptr;

public:
  // setup
  Application(GLFWwindow *);

  // disable copy constructors (for safety)
  Application(const Application &) = delete;
  Application &operator=(const Application &) = delete;

  // rendering callbacks (every frame)
  void render();
  void renderGUI();
  void updateCameraMovement(int w, int h);
};