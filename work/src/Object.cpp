// Object.cpp
#include "Object.hpp"
#include <iostream>

Object::Object() : material(nullptr) {}
Object::Object(const gl_mesh &mesh, Material *material)
    : mesh(mesh), material(material) {}
Object::Object(const gl_mesh &mesh) : mesh(mesh), material(nullptr) {}

Material *Object::getMaterial() { return material; }

void Object::setMaterial(Material *mat) { material = mat; }

void Object::draw(const glm::mat4 &view, const glm::mat4 &proj) {
  // Draw the object using the material
  std::cout << "Drawing object with material: " << material->getName()
            << std::endl;

  material->bind();
  material->setUniforms(view, proj);

  mesh.draw();
  material->unbind();
}
