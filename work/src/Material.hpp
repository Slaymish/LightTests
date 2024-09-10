#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Shader.hpp"

class Material {
public:
  void bind();
  void unbind();
  void setUniforms();

private:
  Shader *shader;
  // Material properties like textures, colors, etc.
};

#endif // MATERIAL_HPP
