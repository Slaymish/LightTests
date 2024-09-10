#include "Camera.hpp"

Camera::Camera()
    : position(0.0f, 0.0f, 0.0f), direction(0.0f, 0.0f, -1.0f),
      up(0.0f, 1.0f, 0.0f) {}

void Camera::setPosition(const glm::vec3 &pos) { position = pos; }

void Camera::setDirection(const glm::vec3 &dir) { direction = dir; }

void Camera::setUp(const glm::vec3 &up) { this->up = up; }

glm::vec3 Camera::getPosition() { return position; }

glm::vec3 Camera::getDirection() { return direction; }

glm::vec3 Camera::getUp() { return up; }

void Camera::setProjectionMatrix(glm::mat4 projectionMatrix) {
  this->projectionMatrix = projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() { return viewMatrix; }

glm::mat4 Camera::getProjectionMatrix() { return projectionMatrix; }

void Camera::update() {
  viewMatrix = glm::lookAt(position, position + direction, up);
}
