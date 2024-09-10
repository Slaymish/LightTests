
#include <glm/glm.hpp>

#ifndef LIGHT_HPP
#define LIGHT_HPP

class Light {
public:
  // Light methods and data go here
  void setPosition(const glm::vec3 &pos);
  void setColor(const glm::vec3 &color);
  // Additional light properties
};

#endif // LIGHT_HPP
