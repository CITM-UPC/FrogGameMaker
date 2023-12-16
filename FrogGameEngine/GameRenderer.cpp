#include "GameRenderer.h"

#include <GL/glew.h>

static inline void glVec3(const vec3& v) { glVertex3dv(&v.x); }

Frustum Camera::createFrustum()
{
	Frustum frustum;

	const vec3 front = glm::normalize(eye - center);
	const vec3 right = glm::cross(glm::normalize(up), front);

	const float halfVSide = zFar * tanf(fov * .5f);
	const float halfHSide = halfVSide * aspect;
	const vec3 frontMultFar = zFar * front;


	frustum.nearFace = { front, zNear };
	frustum.farFace = { -front, zFar };
	frustum.rightFace = { eye, 0 };
	frustum.leftFace = { eye, 0 };
	frustum.topFace = { eye, 0 };
	frustum.bottomFace = { eye, 0 };

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

	vec3 a = { zNear * -sin(fov / 2) * aspect, zNear * sin(fov / 2), zNear };
	vec3 b = { zNear * sin(fov / 2) * aspect, zNear * sin(fov / 2), zNear };
	vec3 c = { zNear * -sin(fov / 2) * aspect, zNear * -sin(fov / 2), zNear };
	vec3 d = { zNear * sin(fov / 2) * aspect, zNear * -sin(fov / 2), zNear };

	vec3 e = { zFar * -sin(fov / 2) * aspect, zFar * sin(fov / 2), zFar };
	vec3 f = { zFar * sin(fov / 2) * aspect, zFar * sin(fov / 2), zFar };
	vec3 g = { zFar * -sin(fov / 2) * aspect, zFar * -sin(fov / 2), zFar };
	vec3 h = { zFar * sin(fov / 2) * aspect, zFar * -sin(fov / 2), zFar };


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
