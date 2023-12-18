#pragma once

#include "Types.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

struct Plane
{
	// unit vector
	vec3 normal = { 0.0f, 1.0f, 0.0f };

	// position
	vec3 pos = { 0, 0, 0 };
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

	// local frustum, will have to apply transformation before using it
	Frustum createFrustum();

	// local frustum, will have to apply transformation before using it
	Frustum createFrustum(mat4 transform);

	// local frustum, will be drawn after applying the transform matrix in the render
	void drawFrustum();

	Camera() : fov(60), aspect(16.0 / 9.0), zNear(0.1), zFar(100) {}
};
