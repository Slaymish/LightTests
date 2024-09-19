#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>

// glm
#include <glm/gtc/matrix_transform.hpp>

// project
#include "Camera.hpp"
#include "opengl.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

mat4 Camera::viewMatrix() const {
  // Create a translation matrix that represents the camera position
  mat4 translationMatrix = translate(mat4(1.0f), m_position);

  // Create a rotation matrix that represents the camera rotation
  mat4 rotationMatrix = mat4_cast(glm::quat(m_rotation));

  // Combine the translation and rotation matrices
  mat4 viewMatrix = rotationMatrix * translationMatrix;

  return viewMatrix;
}

mat4 Camera::projectionMatrix() const {
  // Create a perspective projection matrix
  mat4 projectionMatrix = perspective(
      radians(m_fovy), m_image_size.x / m_image_size.y, 0.1f, 100.0f);

  return projectionMatrix;
}

void Camera::setPositionOrientation(const vec3 &pos, float yaw, float pitch) {
  m_position = pos;
  m_yaw = yaw;
  m_pitch = pitch;

  // update rotation matrix (based on yaw and pitch)
  m_rotation = rotate(mat4(1), -m_yaw, vec3(0, 1, 0)) *
               rotate(mat4(1), -m_pitch, vec3(1, 0, 0));
}

Ray Camera::generateRay(const vec2 &pixel) {
  //-------------------------------------------------------------
  // [Assignment] :
  // Generate a ray in the scene using the camera position,
  // rotation, field of view on the y axis (fovy), and the image
  // size. The pixel is given in image coordinates [0, imagesize]
  // This COULD be done by first creating the ray in ViewSpace
  // then transforming it by the position and rotation to get
  // it into worldspace.
  //-------------------------------------------------------------

  Ray ray;

  // Image dimensions
  float imageWidth = float(m_image_size.x);
  float imageHeight = float(m_image_size.y);

  // Convert Pixel to NDC
  float ndcX = (2.0f * pixel.x / imageWidth) - 1.0f;
  float ndcY = (2.0f * pixel.y / imageHeight) - 1.0f;

  // Compute Camera Space Coordinates
  float aspect = imageWidth / imageHeight;
  float tanFovy = tan(radians(m_fovy) / 2.0f);
  float cameraX = ndcX * aspect * tanFovy;
  float cameraY = ndcY * tanFovy;
  vec3 rayDirCameraSpace = normalize(vec3(cameraX, cameraY, -1.0f));

  glm::quat rotation = glm::quat(m_rotation);
  glm::mat4 rotationMatrix = glm::mat4_cast(rotation);

  // Transform the Ray to World Space
  mat4 viewToWorld =
      inverse(translate(mat4(1.0f), m_position) * rotationMatrix);
  vec3 rayDirWorldSpace = vec3(viewToWorld * vec4(rayDirCameraSpace, 0.0f));

  ray.origin = m_position;
  ray.direction = rayDirWorldSpace; // Direction in world space

  return ray;
}