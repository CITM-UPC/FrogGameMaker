#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* owner) : Component(owner)
{
	_transform = mat4(1.0f);
	componentType = TRANSFORM;
}

TransformComponent::~TransformComponent()
{

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
	vec3 rotEulerAngles;
	double Yaw, Pitch, Roll;
	if (toleranceCheckFix(_transform[2][0], 1) == 1)
	{
		Yaw = glm::half_pi<float>();
		Pitch = atan2(_transform[1][2], _transform[1][1]);
		Roll = 0;

	}
	else if (toleranceCheckFix(_transform[2][0], -1) == -1)
	{
		Yaw = 3 * glm::half_pi<float>();
		Pitch = atan2(_transform[1][2], _transform[1][1]);
		Roll = 0;
	}
	else
	{

		Yaw = asin(-_transform[2][0]);
		Pitch = atan2(_transform[2][1], _transform[2][2]);
		Roll = atan2(_transform[1][0], _transform[0][0]);
	}

	rotEulerAngles.x = Pitch;
	rotEulerAngles.y = Yaw;
	rotEulerAngles.z = Roll;

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
