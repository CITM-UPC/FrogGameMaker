#pragma once
#include <string>
#include <list>
#include "Component.h"

using namespace std;

class GameObject {
public:
	GameObject() {
		name = "test";

		// testing
		AddComponent(TRANSFORM);
		AddComponent(MESH);
		AddComponent(TEXTURE);
	}
	GameObject(string name) {
		this->name = name;

		// testing
		AddComponent(TRANSFORM);
		AddComponent(MESH);
		AddComponent(TEXTURE);
	};

	void addChild(GameObject* child) {
		if (child->_parent == this) return;
		if (child->_parent) child->_parent->removeChild(child);
		children.push_back(child);
		child->_parent = this;
	};
	void removeChild(GameObject* child) {
		children.remove(child);
		child->_parent = nullptr;
	};

	Component* AddComponent(ComponentType type) {

		Component* newComponent = nullptr;

		switch (type)
		{
		case NONE:
			break;
		case TRANSFORM:
			newComponent = new TransformComponent();
			break;
		case MESH:
			newComponent = new MeshComponent();
			break;
		case TEXTURE:
			newComponent = new TextureComponent();
			break;
		default:
			break;
		}

		components.push_back(newComponent);

		return newComponent;
		
	}

	Component* GetComponent(ComponentType type) {

		for (auto i = components.begin(); i != components.end(); ++i) {
			if ((*i)->componentType == type) {
				return *i;
			}
		}
		return nullptr;
	}

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;
	GameObject* _parent;
	
	list<Component*> components;
};