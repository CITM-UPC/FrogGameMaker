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

	unique_ptr<GameObject> FindChild(GameObject* child);

	// if toParent is nullptr the child goes to the scene
	void MoveChildToAnotherParent(GameObject* child, GameObject* toParent = nullptr);

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
	list<unique_ptr<GameObject>> children;

};