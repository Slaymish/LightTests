#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP

#include "ILightTechnique.hpp"
#include "ray.hpp"

class PathTracer : public ILightTechnique {
private:
  int maxDepth = 5;
  Scene *scene;

public:
  PathTracer() = default;
  virtual ~PathTracer();
  void initialize(Scene &scene) override;
  void render(Camera *camera) override;
  void cleanup() override;
  glm::vec3 sampleRay(const Ray &ray, int depth);
};

#endif // PATHTRACER_HPP