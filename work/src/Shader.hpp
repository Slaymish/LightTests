
#include <string>

#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
  void bind();
  void unbind();
  void setUniform(const std::string &name, float value);
  // Add other uniform-setting methods here
};

#endif // SHADER_HPP
