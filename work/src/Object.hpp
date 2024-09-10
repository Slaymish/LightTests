#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Material.hpp"

class Object {
public:
  // Object methods and data go here, including mesh and material handling
  Material *getMaterial();
  void setMaterial(Material *mat);

private:
  Material *material;
  // Mesh and other object properties
};

#endif // OBJECT_HPP
