#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Camera.hpp"
#include "Material.hpp"
#include "RayHit.hpp"
#include "cgra/cgra_mesh.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>

using namespace cgra;

class Object {
public:
  Object();
  Object(const gl_mesh &mesh, Material *material);
  Object(const gl_mesh &mesh);
  ~Object() = default;

  // Object methods and data go here, including mesh and material handling
  Material *getMaterial();
  void setMaterial(Material *mat);

  gl_mesh getMesh() { return mesh; }
  void setMesh(const gl_mesh &m) { mesh = m; }

  void draw(Camera *camera);

  RayHit intersect(const Ray &ray);

private:
  Material *material;
  gl_mesh mesh;
  // Mesh and other object properties
};

#endif // OBJECT_HPP
