
// std
#include <chrono>
#include <iostream>
#include <string>

// glm
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

// project
#include "PhotonMapping.hpp"
#include "TestTechnique.hpp"
#include "ThreePassTechnique.hpp"
#include "PathTracer.hpp"
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

  // set a lighting technique 
  m_renderer.setTechnique(new TestTechnique());

  // Initialize the scene and renderer
  m_renderer.initialize();

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

  // Set the camera in the scene
  m_camera = Camera();
  m_camera.setPosition(glm::vec3(0.0, 0.0, m_distance));
  m_camera.setDirection(glm::vec3(0.0, 0.0, -1.0));
  m_camera.setUp(glm::vec3(0.0, 1.0, 0.0));
}

void Application::render() {

  // retrieve the window hieght
  int width, height;
  glfwGetFramebufferSize(m_window, &width, &height);

  m_windowsize = vec2(width, height); // update window size
  glViewport(0, 0, width,
             height); // set the viewport to draw to the entire window

  // clear the back-buffer
  glClearColor(1,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // enable flags for normal/forward rendering
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // projection matrix
  mat4 proj = perspective(1.f, float(width) / height, 0.1f, 1000.f);

  // Set the camera in the scene
  m_camera.setProjectionMatrix(proj);

  glPolygonMode(GL_FRONT_AND_BACK, (m_showWireframe) ? GL_LINE : GL_FILL);

  // Call the renderer to render the scene
  m_renderer.renderFrame(m_scene, m_camera);
}

void Application::renderGUI() {

  // setup window
  ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiSetCond_Once);
  ImGui::Begin("Options", 0);

  ImGui::Text("Application %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  // display current camera parameters

  // ImGui::SliderFloat("Pitch", &m_pitch, -pi<float>() / 2, pi<float>() / 2,
  //  "%.2f");
  // ImGui::SliderFloat("Yaw", &m_yaw, -pi<float>(), pi<float>(), "%.2f");
  // ImGui::SliderFloat("Distance", &m_distance, 0, 100, "%.2f", 2.0f);

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
      m_renderer.setTechnique(new TestTechnique());
    }
    ImGui::SameLine();
    if (ImGui::Button("Photon Mapping")) {
      m_renderer.setTechnique(new PhotonMapping());
    }
    if (ImGui::Button("Three Pass")) {
      m_renderer.setTechnique(new ThreePassTechnique());
    }
    if (ImGui::Button("Path Tracing")) {
      m_renderer.setTechnique(new PathTracer());
    }
  }
  
  // finish creating window
  ImGui::End();
}

void Application::updateCameraMovement(int w, int h) {
  //m_restart_render = false;
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
    m_restart_render = true;
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
    m_restart_render = true;
  }

  m_camera->setPositionOrientation(pos, yaw, pitch);
}

void Application::cursorPosCallback(double xpos, double ypos) {
  if (m_leftMouseDown) {
    vec2 whsize = m_windowsize / 2.0f;

    // clamp the pitch to [-pi/2, pi/2]
    m_pitch += float(
        acos(glm::clamp((m_mousePosition.y - whsize.y) / whsize.y, -1.0f,
                        1.0f)) -
        acos(glm::clamp((float(ypos) - whsize.y) / whsize.y, -1.0f, 1.0f)));
    m_pitch = float(glm::clamp(m_pitch, -pi<float>() / 2, pi<float>() / 2));

    // wrap the yaw to [-pi, pi]
    m_yaw += float(
        acos(glm::clamp((m_mousePosition.x - whsize.x) / whsize.x, -1.0f,
                        1.0f)) -
        acos(glm::clamp((float(xpos) - whsize.x) / whsize.x, -1.0f, 1.0f)));
    if (m_yaw > pi<float>())
      m_yaw -= float(2 * pi<float>());
    else if (m_yaw < -pi<float>())
      m_yaw += float(2 * pi<float>());
  }

  // updated mouse position
  m_mousePosition = vec2(xpos, ypos);
}

void Application::mouseButtonCallback(int button, int action, int mods) {
  (void)mods; // currently un-used

  // capture is left-mouse down
  if (button == GLFW_MOUSE_BUTTON_LEFT)
    m_leftMouseDown =
        (action == GLFW_PRESS); // only other option is GLFW_RELEASE
}

void Application::scrollCallback(double xoffset, double yoffset) {
  (void)xoffset; // currently un-used
  m_distance *= pow(1.1f, -yoffset);
}

void Application::keyCallback(int key, int scancode, int action, int mods) {
  (void)key, (void)scancode, (void)action, (void)mods; // currently un-used
}

void Application::charCallback(unsigned int c) {
  (void)c; // currently un-used
}
