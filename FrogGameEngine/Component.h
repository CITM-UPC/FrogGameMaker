#pragma once
#include "Types.h"
#include "Mesh.h"
#include "Texture2D.h"
#include <glm/ext/matrix_transform.hpp>
#include <list>

enum ComponentType {
	NONE = 0,
	TRANSFORM,
	MESH,
	TEXTURE,
	CAMERA

};

class Component {
public:
	virtual void Start() {};
	virtual void Update() {};
	virtual void Render() {};

	ComponentType componentType = NONE;
};
