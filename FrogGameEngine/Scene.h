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

	void DebugStart() {
		{
			GameObject* tempGO = new GameObject("GameObject 1");
			children.push_back(tempGO);
		}
		{
			GameObject* tempGO = new GameObject("GameObject 2");
			children.push_back(tempGO);
			GameObject* tempGO2 = new GameObject("GameObject 3");
			tempGO->addChild(tempGO2);
		}
		{
			GameObject* tempGO = new GameObject("GameObject 4");
			children.push_back(tempGO);
		}
	};

	// --TODO--
	void Start() {};

	// --TODO--
	void Update() {};

	void CleanUp() {};

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;
	


};