#include "GameRenderer.h"

#include <GL/glew.h>

static inline void glVec3(const vec3& v) { glVertex3dv(&v.x); }

Frustum Camera::createFrustum()
{
	Frustum frustum;

	const vec3 front = { 0, 0, 1 };
	const vec3 right = { 1, 0, 0 };
	const vec3 up = { 0, 1, 0 };

	frustum.nearFace = { front, {0, 0, zNear} };
	frustum.farFace = { -front, {0, 0, zFar} };

	frustum.rightFace = { glm::rotate(front,  -glm::radians(90 - ((fov * 0.5) * aspect)), up), {0, 0, 0} };
	frustum.leftFace = { glm::rotate(front, glm::radians(90 - ((fov * 0.5) * aspect)), up), {0, 0, 0} };

	frustum.topFace = { glm::rotate(front, -glm::radians(90 - (fov * 0.5)), right), {0, 0, 0} };
	frustum.bottomFace = { glm::rotate(front, glm::radians(90 - (fov * 0.5)), right), {0, 0, 0} };

	return frustum;
}

Frustum Camera::createFrustum(mat4 transform)
{
	Frustum frustum;

	const vec3 right = transform[0];
	const vec3 upUp = transform[1];
	const vec3 front = transform[2];
	const vec3 pos = transform[3];

	frustum.nearFace = { front, pos + (front * zNear) };
	frustum.farFace = { -front, pos + (front * zFar) };

	frustum.rightFace = { glm::rotate(front,  -glm::radians(90 - ((fov * 0.5) * aspect)), upUp), pos };
	frustum.leftFace = { glm::rotate(front, glm::radians(90 - ((fov * 0.5) * aspect)), upUp), pos };

	frustum.topFace = { glm::rotate(front, -glm::radians(90 - (fov * 0.5)), right), pos };
	frustum.bottomFace = { glm::rotate(front, glm::radians(90 - (fov * 0.5)), right), pos };

	return frustum;
}

void Camera::drawFrustum()
{
	//     e --------- f
	//     |           |
	//     |           |
	//     |           |
	//     g --------- h


	// a --- b
	// |     |
	// c --- d

	double verticalFovDistance = sin(glm::radians(fov / 2));

	vec3 a = { zNear * -verticalFovDistance * aspect, zNear * verticalFovDistance, zNear };
	vec3 b = { zNear * verticalFovDistance * aspect, zNear * verticalFovDistance, zNear };
	vec3 c = { zNear * -verticalFovDistance * aspect, zNear * -verticalFovDistance, zNear };
	vec3 d = { zNear * verticalFovDistance * aspect, zNear * -verticalFovDistance, zNear };

	vec3 e = { zFar * -verticalFovDistance * aspect, zFar * verticalFovDistance, zFar };
	vec3 f = { zFar * verticalFovDistance * aspect, zFar * verticalFovDistance, zFar };
	vec3 g = { zFar * -verticalFovDistance * aspect, zFar * -verticalFovDistance, zFar };
	vec3 h = { zFar * verticalFovDistance * aspect, zFar * -verticalFovDistance, zFar };


	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	glVec3(a);
	glVec3(b);
	glVec3(d);
	glVec3(c);
	glVec3(a);

	glVec3(e);
	glVec3(f);
	glVec3(h);
	glVec3(g);
	glVec3(e);
	glEnd();

	glBegin(GL_LINES);
	glVec3(h);
	glVec3(d);
	glVec3(f);
	glVec3(b);
	glVec3(g);
	glVec3(c);
	glEnd();
	
}