// Material.cpp
#include "Material.hpp"
#include <glm/gtc/type_ptr.hpp>

Material::Material(GLuint s) : shader(s) {}

Material::Material(GLuint s, const std::string &n) : shader(s), name(n) {}

void Material::bind() {
  // shader is a pointer to a GLuint
  glUseProgram(shader);
}

void Material::unbind() { glUseProgram(0); }

void Material::setUniforms(glm::mat4 view, glm::mat4 proj) {

  // uniform mat 4uProjectionMatrix
  // uniform mat4 uModelViewMatrix;

  glUniformMatrix4fv(glGetUniformLocation(shader, "uProjectionMatrix"), 1,
      false, value_ptr(proj));
  glUniformMatrix4fv(glGetUniformLocation(shader, "uModelViewMatrix"), 1, false,
      value_ptr(view));
  glUniform3fv(glGetUniformLocation(shader, "uColor"), 1, value_ptr(m_color));
}
