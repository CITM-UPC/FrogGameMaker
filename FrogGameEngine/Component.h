#pragma once

enum ComponentType {
	TRANSFORM,
	MESH,
	TEXTURE,
	CAMERA,
	PARTICLE_SYSTEM
};

class GameObject;

class Component {
public:
	Component(GameObject* owner) { this->owner = owner; };
	~Component() {};
	virtual void Start() {};
	virtual void Update(double dt) {};
	virtual void Render() {};

	ComponentType componentType = TRANSFORM;
	//const string getOwnerName() { return owner->name };

protected:
	// used to connect to other components
	GameObject* owner;

private: 

};
