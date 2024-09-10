#include <glm/glm.hpp>

#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
private:
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;

  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 up;

public:
  Camera();
  ~Camera() = default;

  void update();

  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();

  glm::vec3 getPosition();
  glm::vec3 getDirection();
  glm::vec3 getUp();

  // void setViewMatrix(glm::mat4 viewMatrix);
  void setProjectionMatrix(glm::mat4 projectionMatrix);

  // Setters
  void setPosition(const glm::vec3 &pos);
  void setDirection(const glm::vec3 &dir);
  void setUp(const glm::vec3 &up);
};

#endif // CAMERA_HPP