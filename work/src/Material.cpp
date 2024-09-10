// Material.cpp
#include "Material.hpp"

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

  // Get the uniform locations
  GLint uProjectionMatrix = glGetUniformLocation(shader, "uProjectionMatrix");
  GLint uModelViewMatrix = glGetUniformLocation(shader, "uModelViewMatrix");

  // Set the uniforms
  glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, &proj[0][0]);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, &view[0][0]);
}
