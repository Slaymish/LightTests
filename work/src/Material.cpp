// Material.cpp
#include "Material.hpp"

void Material::bind() {
  shader->bind();
  setUniforms();
}

void Material::unbind() { shader->unbind(); }

void Material::setUniforms() {
  // Set uniforms like texture, color, etc.
}
