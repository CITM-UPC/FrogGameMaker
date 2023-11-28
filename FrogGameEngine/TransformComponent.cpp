#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	_transform = mat4(1.0f);
	componentType = TRANSFORM;
}

mat4& TransformComponent::getTransform()
{
	return _transform;
}

vec3& TransformComponent::getPosition()
{
	return _pos;
}

vec3& TransformComponent::getRotation()
{

	vec3 inverseScaleVec;
	inverseScaleVec.x = 1.0 / getScale().x;
	inverseScaleVec.y = 1.0 / getScale().y;
	inverseScaleVec.z = 1.0 / getScale().z;

	// get rotation matrix
	glm::dmat3 rotationMatrix;
	rotationMatrix[0][0] = _right[0] * inverseScaleVec.x;
	rotationMatrix[0][1] = _up[0] * inverseScaleVec.x;
	rotationMatrix[0][2] = _forward[0] * inverseScaleVec.x;

	rotationMatrix[1][0] = _right[1] * inverseScaleVec.y;
	rotationMatrix[1][1] = _up[1] * inverseScaleVec.y;
	rotationMatrix[1][2] = _forward[1] * inverseScaleVec.y;

	rotationMatrix[2][0] = _right[2] * inverseScaleVec.z;
	rotationMatrix[2][1] = _up[2] * inverseScaleVec.z;
	rotationMatrix[2][2] = _forward[2] * inverseScaleVec.z;

	// get rotation euler angles
	vec3 rotEulerAngles;
	rotEulerAngles.y = -glm::asin(rotationMatrix[2][0]);

	rotEulerAngles.x = glm::acos(rotationMatrix[0][0]);
	rotEulerAngles.z = glm::asin(rotationMatrix[2][0]);

	if (toleranceCheckFix(-rotationMatrix[2][0] - 1) + 1 == 1) {
		rotEulerAngles.y = 90;
		rotEulerAngles.x = atan2(rotationMatrix[1][2], rotationMatrix[1][1]);
		rotEulerAngles.z = 0;
	}
	else if (toleranceCheckFix(-rotationMatrix[2][0] + 1) - 1 == -1) {
		rotEulerAngles.y = 3 * 90;
		rotEulerAngles.x = atan2(rotationMatrix[1][2], rotationMatrix[1][1]);
		rotEulerAngles.z = 0;
	}
	else {
		rotEulerAngles.y = asin(-rotationMatrix[2][0]);
		rotEulerAngles.z = atan2(rotationMatrix[2][1], rotationMatrix[2][2]);
		rotEulerAngles.x = atan2(rotationMatrix[1][0], rotationMatrix[0][0]);
	}

	return rotEulerAngles;
}

vec3 TransformComponent::getScale()
{
	double x = glm::length(_right);
	double y = glm::length(_up);
	double z = glm::length(_forward);

	return vec3(x, y, z);
}

void TransformComponent::translate(vec3 translation, ReferenceAxis ref)
{
	switch (ref)
	{
	case LOCAL:
		_transform = glm::translate(_transform, translation);
		break;
	case GLOBAL:
		_pos += translation;
		break;
	default:
		break;
	}
}

void TransformComponent::rotate(double degrees, const vec3& axis)
{
	_transform = glm::rotate(_transform, glm::radians(degrees), axis);
}

void TransformComponent::scale(vec3 scale)
{
	_transform = glm::scale(_transform, scale);
}

double TransformComponent::toleranceCheckFix(double n, int c)
{
	if (abs(n - c) < 1e-5) {
		n = c;
	}

	return n;
}
