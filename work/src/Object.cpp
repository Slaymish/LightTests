// Object.cpp
#include "Object.hpp"
#include <iostream>

Object::Object() : material(nullptr) {}
Object::Object(const gl_mesh &mesh, Material *material)
    : mesh(mesh), material(material) {}
Object::Object(const gl_mesh &mesh) : mesh(mesh), material(nullptr) {}

Material *Object::getMaterial() { return material; }

void Object::setMaterial(Material *mat) { material = mat; }

void Object::draw(Camera *camera) {
  // Draw the object using the material
  std::cout << "Drawing object with material: " << material->getName()
            << std::endl;

  // Get the view and projection matrices from the camera
  glm::mat4 view = camera->viewMatrix();
  glm::mat4 proj = camera->projectionMatrix();

  material->bind();
  material->setUniforms(view, proj);

  mesh.draw();
  material->unbind();
}

RayHit Object::intersect(const Ray &ray) {
  // Perform intersection tests with the object
  RayHit hit;
  hit.hit = false;
  hit.m_distance = std::numeric_limits<float>::infinity();

  // Perform intersection tests with the object's mesh
  // For now, just return a dummy hit
  return hit;
}
