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

  void setColor(const glm::vec3 &c) { m_color = c; }
  glm::vec3 getColor() { return m_color; }

  void setIsLight(bool l) { m_isLight = l; }
  bool getIsLight() { return m_isLight; }

private:
  GLuint shader;
  std::string name = "Material";
  glm::vec3 m_color = glm::vec3(0.8);
  bool m_isLight = false;

  // Material properties like textures, colors, etc.
};

#endif // MATERIAL_HPP
