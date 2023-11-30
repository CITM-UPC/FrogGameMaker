#pragma once
#include <string>
#include <list>

#include <memory>

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

	~GameObject();

	GameObject* AddNewChildren();
	GameObject* AddNewChildren(GameObjectTypes GOType);

	void AddChild(unique_ptr<GameObject> child);
	unique_ptr<GameObject> RemoveChild(GameObject* child);

	// THE CHILD IS MOVED, THE REFERENCE IS LOST, THE CHILD HAS TO BE MOVED AGAIN
	unique_ptr<GameObject> FindChild(GameObject* child);

	Component* AddComponent(ComponentType type);

	Component* GetComponent(ComponentType type);

	void AddMeshWithTexture(std::vector<Mesh::Ptr> meshes);
	void AddMeshWithTexture(Mesh::Ptr meshes);

	void Render();

	// uuid id
	string name;
	// should be a list of uuids
	list<unique_ptr<GameObject>> children;
	GameObject* _parent = nullptr;
	
	list<unique_ptr<Component>> components;
};