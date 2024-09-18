#include <glm/glm.hpp>

#include "PathTracer.hpp"


using namespace glm;

vec3 PathTracer::sampleRay(const Ray &ray, int depth) {
    RayHit intersect = scene->intersect(ray);

    // If the ray missed, return the background color
    if (!intersect.hit) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    // If the ray hit a light, return the light color
    if (intersect.material->isLight) {
        return intersect.material->color;
    }
}


void PathTracer::initialize(Scene &scene) {
    this->scene = &scene;
}

void PathTracer::render(Camera &camera) {
    // Loop over all pixels in the image
    for (int y = 0; y < camera.height; y++) {
        for (int x = 0; x < camera.width; x++) {
            // Generate a ray through the center of the pixel
            Ray ray = camera.generateRay(x, y);

            // Sample the ray
            vec3 color = sampleRay(ray, 0);

            // Set the pixel color
            camera.setPixel(x, y, color);
        }
    }
}