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
	GameObject() {
		name = "test";

		// testing
		AddComponent(TRANSFORM);
		
	}
	GameObject(string name) {
		this->name = name;

		// testing
		AddComponent(TRANSFORM);

	};
	GameObject(GameObjectTypes type, string name) {
		this->name = name;

		switch (type)
		{
		case EMPTY:
			AddComponent(ComponentType::TRANSFORM);
			break;
		case OBJECT:
			AddComponent(ComponentType::TRANSFORM);
			AddComponent(ComponentType::MESH);
			AddComponent(ComponentType::TEXTURE);
			break;
		case CAMERA_OBJECT:
			AddComponent(ComponentType::TRANSFORM);
			AddComponent(ComponentType::CAMERA);
			break;
		default:
			break;
		}
	};

	GameObject* AddNewChildren() {
		string gameObjectName = name + " " + std::to_string(children.size());

		GameObject* tempGO = new GameObject(gameObjectName);
		addChild(tempGO);
		return tempGO;

	}

	GameObject* AddNewChildren(GameObjectTypes GOType) {
		string gameObjectName = name + " " + std::to_string(children.size());

		GameObject* tempGO = nullptr;

		switch (GOType)
		{
		case EMPTY:
			tempGO = new GameObject(EMPTY, gameObjectName);
			break;
		case OBJECT:
			tempGO = new GameObject(OBJECT, gameObjectName);
			break;
		case CAMERA_OBJECT:
			tempGO = new GameObject(CAMERA_OBJECT, gameObjectName);
			break;
		default:
			break;
		}

		addChild(tempGO);
		return tempGO;

	}

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
		case ComponentType::NONE:
			break;
		case ComponentType::TRANSFORM:
			newComponent = new TransformComponent();
			break;
		case ComponentType::MESH:
			newComponent = new MeshComponent();
			break;
		case ComponentType::TEXTURE:
			newComponent = new TextureComponent();
			break;
		case ComponentType::CAMERA:
			newComponent = new CameraComponent();
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

	void AddMeshWithTexture(std::vector<Mesh::Ptr> meshes) {
		
		if (meshes.size() == 1) {
			if (GetComponent(MESH) == nullptr) {
				AddComponent(MESH);
			}
			if (GetComponent(TEXTURE) == nullptr) {
				AddComponent(TEXTURE);
			}
			MeshComponent* mesh = (MeshComponent*)GetComponent(MESH);
			mesh->setMesh(*meshes.begin());
			TextureComponent* texture = (TextureComponent*)GetComponent(TEXTURE);
			texture->setTexture((*meshes.begin())->texture);
		}
		else {
			for (auto i = meshes.begin(); i != meshes.end(); ++i) {
				GameObject* GOPart = AddNewChildren(OBJECT);
				MeshComponent* meshPart = (MeshComponent*)GOPart->GetComponent(MESH);
				meshPart->setMesh(*i);
				TextureComponent* texturePart = (TextureComponent*)GOPart->GetComponent(TEXTURE);
				texturePart->setTexture((*i)->texture);
			}
		}
	}

	void AddMeshWithTexture(Mesh::Ptr meshes) {
		if (GetComponent(MESH) == nullptr) {
			AddComponent(MESH);
		}
		if (GetComponent(TEXTURE) == nullptr) {
			AddComponent(TEXTURE);
		}
		MeshComponent* mesh = (MeshComponent*)GetComponent(MESH);
		mesh->setMesh(meshes);
		TextureComponent* texture = (TextureComponent*)GetComponent(TEXTURE);
		texture->setTexture(meshes->texture);
	}

	void Render() {
		bool toRender = true;
		// get necessary components
		TransformComponent* transform = (TransformComponent*)GetComponent(TRANSFORM);
		if (GetComponent(MESH) == nullptr) {
			toRender = false;
		}

		glPushMatrix();
		glMultMatrixd(&transform->getTransform()[0].x);

		if (toRender) {
			MeshComponent* mesh = (MeshComponent*)GetComponent(MESH);
			if (mesh->getMesh()) mesh->getMesh()->draw();
		}

		// render
		for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
			(*childIt)->Render();
		}

		glPopMatrix();

	}

	// uuid id
	string name;
	// should be a list of uuids
	list<GameObject*> children;
	GameObject* _parent;
	
	list<Component*> components;
};