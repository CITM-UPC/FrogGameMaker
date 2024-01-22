#pragma once
// only has information of itself
// the emmiter can change part of its values

// instead of having initColor and endColor, having deltaColor and multiplying it with dt and adding it to the color

#include "Types.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"


class Particle {
public:
	float duration;
	float lifetime;

	// Color color
	// Color deltaColor

	vec3 position;
	glm::quat rotation;
	vec3 scale;

private: 
	
};