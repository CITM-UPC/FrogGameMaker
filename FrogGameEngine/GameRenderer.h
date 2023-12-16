#pragma once

#include "Types.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

struct Plane
{
	// unit vector
	vec3 normal = { 0.0f, 1.0f, 0.0f };

	// distance from origin to the nearest point in the plane
	// (?) distance only to z
	double distance = 0.0f;
};

struct Frustum
{
	Plane topFace;
	Plane bottomFace;

	Plane rightFace;
	Plane leftFace;

	Plane farFace;
	Plane nearFace;
};

struct Camera
{
	double fov;
	double aspect;
	double zNear;
	double zFar;

	vec3 eye;
	vec3 center;
	vec3 up;

	// local frustum, will have to apply transformation before using it
	Frustum createFrustum();

	// local frustum, will be drawn after applying the transform matrix in the render
	void drawFrustum();

	mat4 computeLookAt() const {
		return glm::lookAt(eye, center, up);
	}

	Camera() : fov(60), aspect(16.0 / 9.0), zNear(0.1), zFar(100), eye(10, 2, 10), center(0, 1, 0), up(0, 1, 0) {}
};
