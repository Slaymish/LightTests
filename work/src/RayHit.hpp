#pragma once

#include <glm/glm.hpp>
#include <limits>

class Object;
class Material;


class RayHit {
public:
	// set to true if there was actually an intersection
	bool m_valid = false;

	// distance along the ray the intersection occured
	float m_distance = std::numeric_limits<float>::infinity();
	
	// position, normal and uv coordinates of the surface
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_uv_coord; // challenge only!

	// pointers to the original shape and material
	Object * m_object = nullptr;
	Material * m_material = nullptr;
};