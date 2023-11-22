#pragma once
#include <string>
#include <list>
#include "GameObject.h"

using namespace std;

class Scene {
public:
	Scene() {
	
	};
	Scene(string name) {
		this->name = name;
	};
	~Scene() {
	
	};

	GameObject* AddGameObject() {
		string gameObjectName = "Game Object " + std::to_string(children.size());

		GameObject* tempGO = new GameObject(gameObjectName);
		children.push_back(tempGO);
		return tempGO;
	}

	GameObject* AddGameObject(string name) {
		GameObject* tempGO = new GameObject(name);
		children.push_back(tempGO);
		return tempGO;

	}

	GameObject* AddGameObjectChildren(GameObject* parent) {
		string gameObjectName = parent->name + " " + std::to_string(parent->children.size());

		GameObject* tempGO = new GameObject(gameObjectName);
		parent->addChild(tempGO);
		return tempGO;

	}

	void DebugStart() {
		{
			AddGameObject();
		}
		{
			GameObject* temp = AddGameObject();
			AddGameObjectChildren(temp);
		}
		{
			AddGameObject();
		}
	};

	// --TODO--
	void Start() {};

	// --TODO--
	void Update() {};

	void Render() {
		for (auto gameObjectI = children.begin(); gameObjectI != children.end(); ++gameObjectI) {
			(*gameObjectI)->Render();
		}
	
	};

	void CleanUp() {
		children.clear();
	};

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;

};