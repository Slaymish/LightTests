#include <glm/glm.hpp>

#include "PathTracer.hpp"
#include "RayHit.hpp"

using namespace glm;

vec3 PathTracer::sampleRay(const Ray &ray, int depth) {
  RayHit intersect = scene->intersect(ray);

  // If the ray missed, return the background color
  if (!intersect.hit) {
    return vec3(0.0f, 0.0f, 0.0f);
  }

  // If the ray hit a light, return the light color
  if (intersect.m_material->getIsLight()) {
    return intersect.m_material->getColor();
  }

  // If the ray hit an object, sample the ray recursively
  vec3 color = vec3(0.0f, 0.0f, 0.0f);
  for (int i = 0; i < 10; i++) {
    vec3 randomDirection =
        normalize(vec3(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX,
                       rand() / (float)RAND_MAX) -
                  vec3(0.5f, 0.5f, 0.5f));
    Ray newRay = Ray(intersect.m_position, randomDirection);
    color += sampleRay(newRay, depth + 1);
  }

  return color / 10.0f;
}

PathTracer::~PathTracer() { cleanup(); }

void PathTracer::cleanup() { scene = nullptr; }

void PathTracer::initialize(Scene &scene) { this->scene = &scene; }

void PathTracer::render(Camera *camera) {
  // Loop over all pixels in the image
  for (int y = 0; y < camera->imageSize().y; y++) {
    for (int x = 0; x < camera->imageSize().x; x++) {
      // Generate a ray for the current pixel
      Ray ray = camera->generateRay(vec2(x, y));

      // Sample the ray
      vec3 color = sampleRay(ray, 0);

      // Set the pixel color
      // camera.setPixel(vec2(x, y), color);
    }
  }
}