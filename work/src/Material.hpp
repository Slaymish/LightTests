#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Shader.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Material {
public:
  Material(GLuint s);
  Material(GLuint s, const std::string &n);
  ~Material() = default;

  void bind();
  void unbind();
  void setUniforms(glm::mat4 view, glm::mat4 proj);

  // Getters and setters
  GLuint getShader() { return shader; }
  void setShader(GLuint s) { shader = s; }

  void setName(const std::string &n) { name = n; }
  std::string getName() { return name; }

private:
  GLuint shader;
  std::string name = "Material";

  // Material properties like textures, colors, etc.
};

#endif // MATERIAL_HPP
