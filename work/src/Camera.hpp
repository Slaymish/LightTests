
#pragma once

// std
#include <chrono>

// project
#include "ray.hpp"

// Simple camera class that stores its world position/rotation
// and the fovy with that imagesize
class Camera {
private:
  // position / orientation / fovy
  glm::vec3 m_position{0};
  float m_pitch = 0;
  float m_yaw = 0;
  glm::mat4 m_rotation;
  float m_fovy = 45;

  // what is the size of the image we have to generate rays for
  glm::vec2 m_image_size{1};

public:
  Camera() { setPositionOrientation(m_position, m_yaw, m_pitch); }

  // feild of view on the y-axis
  // ie. what is the angle of how much we can see vertically

  // typical get methods
  glm::vec3 position() { return m_position; }
  float yaw() { return m_yaw; }
  float pitch() { return m_pitch; }

  glm::mat4 viewMatrix() const;
  glm::mat4 projectionMatrix() const;

  // typical set methods
  void setPositionOrientation(const glm::vec3 &pos, float yaw, float pitch);
  void setImageSize(const glm::vec2 &size) {
    m_image_size = size;
    setPositionOrientation(m_position, m_yaw, m_pitch);
  }

  glm::vec2 imageSize() { return m_image_size; }

  void setFovy(float fovy) { m_fovy = fovy; }

  // converts a position in screen coordinates into a ray in world coordinates
  Ray generateRay(const glm::vec2 &pixel);
};
