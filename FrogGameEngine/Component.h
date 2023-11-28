#pragma once

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

	ComponentType componentType = NONE;
};
