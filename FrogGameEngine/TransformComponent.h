#pragma once
#include "Component.h"
#include "Types.h"
#include <glm/ext/matrix_transform.hpp>

enum ReferenceAxis {
	LOCAL,
	GLOBAL
};

class TransformComponent : public Component {
public:

	TransformComponent();

	mat4& getTransform();

	vec3& getPosition();
	vec3& getRotation();
	vec3 getScale();

	void translate(vec3 translation, ReferenceAxis ref = LOCAL);
	void rotate(double degrees, const vec3& axis);
	void scale(vec3 scale);

private:
	double toleranceCheckFix(double n, int c = 0);

protected:

private:
	union {
		mat4 _transform;
		struct {
			vec3 _right;	double _paddingX;
			vec3 _up;		double _paddingY;
			vec3 _forward;	double _paddingZ;
			vec3 _pos;		double _paddingW;
		};
	};
};