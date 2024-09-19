
// std
#include <chrono>
#include <iostream>
#include <string>

// glm
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

// project
#include "PathTracer.hpp"
#include "PhotonMapping.hpp"
#include "TestTechnique.hpp"
#include "ThreePassTechnique.hpp"
#include "application.hpp"
#include "cgra/cgra_geometry.hpp"
#include "cgra/cgra_gui.hpp"
#include "cgra/cgra_image.hpp"
#include "cgra/cgra_shader.hpp"
#include "cgra/cgra_wavefront.hpp"

using namespace std;
using namespace cgra;
using namespace glm;

void basic_model::draw(const glm::mat4 &view, const glm::mat4 proj) {
  mat4 modelview = view * modelTransform;

  glUseProgram(shader); // load shader and variables
  glUniformMatrix4fv(glGetUniformLocation(shader, "uProjectionMatrix"), 1,
                     false, value_ptr(proj));
  glUniformMatrix4fv(glGetUniformLocation(shader, "uModelViewMatrix"), 1, false,
                     value_ptr(modelview));
  glUniform3fv(glGetUniformLocation(shader, "uColor"), 1, value_ptr(color));

  mesh.draw(); // draw
}

Application::Application(GLFWwindow *window) : m_window(window) {

  shader_builder sb;
  sb.set_shader(GL_VERTEX_SHADER,
                CGRA_SRCDIR + std::string("//res//shaders//color_vert.glsl"));
  sb.set_shader(GL_FRAGMENT_SHADER,
                CGRA_SRCDIR + std::string("//res//shaders//color_frag.glsl"));
  GLuint shader = sb.build();

  // Set the camera in the scene (unique_ptr)
  m_camera = std::make_unique<Camera>();
  m_renderer = std::make_unique<Renderer>();

  // Initialize the scene and renderer
  m_renderer->initialize(m_scene);
  m_renderer->setTechnique(new TestTechnique());

  // Add an object to the scene
  Object *newObject = new Object();
  newObject->setMaterial(new Material(shader, std::string("Basic Material")));
  newObject->setMesh(
      load_wavefront_data(CGRA_SRCDIR + std::string("/res//assets//teapot.obj"))
          .build());

  m_scene.addObject(newObject);

  // Add a light to the scene
  Light *light = new Light();
  light->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
  light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
  m_scene.addLight(light);
}

void Application::render() {

  // retrieve the window hieght
  int width, height;
  glfwGetFramebufferSize(m_window, &width, &height);

  glViewport(0, 0, width,
             height); // set the viewport to draw to the entire window

  // clear the back-buffer
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // enable flags for normal/forward rendering
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glPolygonMode(GL_FRONT_AND_BACK, (m_showWireframe) ? GL_LINE : GL_FILL);

  if (m_moving)
    updateCameraMovement(width, height);

  // Call the renderer to render the scene
  m_renderer->renderFrame(m_camera.get());
}

void Application::renderGUI() {

  // setup window
  ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiSetCond_Once);
  ImGui::Begin("Options", 0);

  ImGui::Text("'P' to toggle camera movement");

  ImGui::Text("Application %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  // helpful drawing options
  if (ImGui::CollapsingHeader("Drawing Options")) {
    ImGui::Checkbox("Wireframe", &m_showWireframe);
    ImGui::SameLine();
    if (ImGui::Button("Screenshot"))
      rgba_image::screenshot(true);

    ImGui::Separator();
  }

  // Render Technique
  if (ImGui::CollapsingHeader("Render Technique")) {
    if (ImGui::Button("Test Technique")) {
      m_renderer->setTechnique(new TestTechnique());
    }
    ImGui::SameLine();
    if (ImGui::Button("Photon Mapping")) {
      m_renderer->setTechnique(new PhotonMapping());
    }
    if (ImGui::Button("Three Pass")) {
      m_renderer->setTechnique(new ThreePassTechnique());
    }
    if (ImGui::Button("Path Tracing")) {
      // m_renderer->setTechnique(new PathTracer());
    }
  }

  // finish creating window
  ImGui::End();
}

vec3 reject(const vec3 &v, const vec3 &direction) {
  vec3 projection = dot(v, direction) * direction;
  return v - projection;
}

void Application::updateCameraMovement(int w, int h) {
  const float rot_speed = 600;
  const float m_speed = 2;

  // calculate movement directions
  vec3 up = vec3(0, 1, 0);
  vec3 forward = normalize(
      reject(rotate(mat4(1), m_camera->yaw(), up) * vec4(0, 0, -1, 0), up));
  vec3 side = normalize(cross(forward, up));

  vec3 pos = m_camera->position();
  float yaw = m_camera->yaw();
  float pitch = m_camera->pitch();

  double x, y;
  glfwGetCursorPos(m_window, &x, &y);
  x -= w * 0.5;
  y -= h * 0.5;
  if (abs(x) > 0.5 || abs(y) > 0.5) {
    yaw += float(-x / rot_speed);
    pitch += float(-y / rot_speed);
    pitch = std::clamp(pitch, -0.49f * pi<float>(), 0.49f * pi<float>());
    glfwSetCursorPos(m_window, w * 0.5, h * 0.5);
  }

  vec3 move{0};

  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    move += forward;
  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    move -= forward;
  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    move -= side;
  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    move += side;
  if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    move -= up;
  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    move += up;

  if (length(move) > 0.1f) {
    auto dpos = normalize(move) * m_speed * m_dt_last;
    pos += dpos;
  }

  m_camera->setPositionOrientation(pos, yaw, pitch);
}
