#pragma once

#include "Types.h"

#include <glm/ext/matrix_transform.hpp>
#include <list>

enum ComponentType {
	NONE = 0,
	TRANSFORM,
	MESH,
	TEXTURE

};

class Component {
public:
	virtual void Start() {};
	virtual void Update() {};

	ComponentType componentType = NONE;
};


class TransformComponent : public Component {
public:

	TransformComponent() {
		_transform = glm::identity<mat4>();
		componentType = TRANSFORM;
	}

	inline vec3 getPosition() { 
		return _transform[3];
	}

	// not in the mood to do rotations --TODO--
	inline vec3 getRotation() {
		return _transform[3];
	}
	
	inline vec3 getScale() { 
		double x = _transform[0].length();
		double y = _transform[1].length();
		double z = _transform[2].length();

		vec3 scale = vec3(x, y, z);

		return scale;
	}

protected:

private:
	mat4 _transform;

};

class MeshComponent : public Component {
public:

	MeshComponent() {
		componentType = MESH;
	}

protected:

private:

};

class TextureComponent : public Component {
public:

	TextureComponent() {
		componentType = TEXTURE;
	}

protected:

private:

};