#include "GameRenderer.h"

#include <GL/glew.h>

static inline void glVec3(const vec3& v) { glVertex3dv(&v.x); }

Frustum Camera::createFrustum()
{
	Frustum frustum;

	const vec3 front = { 0, 0, 1 };
	const vec3 right = { 1, 0, 0 };

	frustum.nearFace = { front, zNear };
	frustum.farFace = { -front, zFar };

	frustum.rightFace = { glm::rotate(front,  -((90 - (fov * 0.5)) * aspect), up), 0};
	frustum.leftFace = { glm::rotate(front, (90 - (fov * 0.5) * aspect), up), 0 };

	frustum.topFace = { glm::rotate(front, -(90 - (fov * 0.5)), right), 0 };
	frustum.bottomFace = { glm::rotate(front, 90 - (fov * 0.5), right), 0 };

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

	double verticalFovDistance = sin(fov / 2);

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
