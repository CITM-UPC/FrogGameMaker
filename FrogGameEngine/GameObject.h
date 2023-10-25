#pragma once
#include <string>
#include <list>
#include "Component.h"

using namespace std;

class GameObject {
public:
	GameObject() {
		name = "test";
		Transform tempTransform;
		components.push_back(tempTransform);
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

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;
	GameObject* _parent;
	
	list<Component> components;
};