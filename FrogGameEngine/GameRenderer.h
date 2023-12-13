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

	/*Frustum createFrustum()	{
		Frustum     frustum;

		const vec3 front = glm::normalize(eye - center);
		const vec3 right = glm::cross(glm::normalize(up), front);

		const float halfVSide = zFar * tanf(fov * .5f);
		const float halfHSide = halfVSide * aspect;
		const vec3 frontMultFar = zFar * front;


		frustum.nearFace = { front, eye + zNear * front };
		frustum.farFace = { eye + frontMultFar, -front };
		frustum.rightFace = { eye,
								glm::cross(frontMultFar - right * halfHSide, up) };
		frustum.leftFace = { eye,
								glm::cross(up, frontMultFar + right * halfHSide) };
		frustum.topFace = { eye,
								glm::cross(right, frontMultFar - up * halfVSide) };
		frustum.bottomFace = { eye,
								glm::cross(frontMultFar + up * halfVSide, right) };

		return frustum;
	}*/

	mat4 computeLookAt() const {
		return glm::lookAt(eye, center, up);
	}

	Camera() : fov(60), aspect(4.0 / 3.0), zNear(0.1), zFar(100), eye(10, 2, 10), center(0, 1, 0), up(0, 1, 0) {}
};
