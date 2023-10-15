#pragma once

#include "Types.h"
#include "glm/ext/matrix_transform.hpp"

struct Camera
{
	double fov;
	double aspect;
	double zNear;
	double zFar;

	vec3 eye;
	vec3 center;
	vec3 up;

	mat4 computeLookAt() const {
		return glm::lookAt(eye, center, up);
	}

	Camera() : fov(60), aspect(4.0 / 3.0), zNear(0.1), zFar(100), eye(10, 2, 10), center(0, 1, 0), up(0, 1, 0) {}
};
