#pragma once
#include <string>
#include <list>
#include "GameObject.h"

using namespace std;

class Scene {
public:
	Scene();
	Scene(string name);
	~Scene();

	GameObject* AddGameObject();
	GameObject* AddGameObject(string name);

	GameObject* AddGameObjectChildren(GameObject* parent);

	void DebugStart();

	// --TODO--
	void Start();

	// --TODO--
	void Update();

	void Render();

	void CleanUp();

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;

};