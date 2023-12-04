#pragma once

enum ComponentType {
	TRANSFORM,
	MESH,
	TEXTURE,
	CAMERA

};

class Component {
public:
	Component() {};
	~Component() {};
	virtual void Start() {};
	virtual void Update() {};

	ComponentType componentType = TRANSFORM;
};
