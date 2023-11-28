#pragma once
#include <string>
#include <list>

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "TextureComponent.h"
#include "CameraComponent.h"

using namespace std;

enum GameObjectTypes {
	EMPTY, 
	OBJECT, 
	CAMERA_OBJECT
};

class GameObject {
public:
	GameObject();
	GameObject(string name);
	GameObject(GameObjectTypes type, string name);

	GameObject* AddNewChildren();

	GameObject* AddNewChildren(GameObjectTypes GOType);

	void addChild(GameObject* child);
	void removeChild(GameObject* child);

	Component* AddComponent(ComponentType type);

	Component* GetComponent(ComponentType type);

	void AddMeshWithTexture(std::vector<Mesh::Ptr> meshes);

	void AddMeshWithTexture(Mesh::Ptr meshes);

	void Render();

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;
	GameObject* _parent;
	
	list<Component*> components;
};