#include "GameObject.h"

#include <GL/glew.h>
#include <memory>

GameObject::GameObject()
{
	name = "test";

	// testing
	AddComponent(TRANSFORM);

}

GameObject::GameObject(string name)
{
	this->name = name;

	// testing
	AddComponent(TRANSFORM);

}

GameObject::GameObject(GameObjectTypes type, string name)
{
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
}

GameObject::~GameObject()
{
	children.clear();
	components.clear();
}

GameObject* GameObject::AddNewChildren()
{
	string gameObjectName = name + " " + to_string(children.size());

	unique_ptr<GameObject> newGameObject = make_unique<GameObject>(gameObjectName);
	GameObject* retGOCopy = newGameObject.get();

	AddChild(move(newGameObject));

	return retGOCopy;
}

GameObject* GameObject::AddNewChildren(GameObjectTypes GOType)
{
	string gameObjectName = name + " " + to_string(children.size());

	unique_ptr<GameObject> newGameObject = make_unique<GameObject>(GOType, gameObjectName);
	GameObject* retGOCopy = newGameObject.get();

	AddChild(move(newGameObject));

	return retGOCopy;
}

void GameObject::AddChild(unique_ptr<GameObject> child)
{
	if (child->_parent == this) return;

	child->_parent = this;
	children.push_back(move(child));
}

unique_ptr<GameObject> GameObject::RemoveChild(GameObject* child)
{
	unique_ptr<GameObject> ptrChild = FindChild(child);
	ptrChild->_parent = nullptr;
	children.remove(ptrChild);

	return move(ptrChild);
}

unique_ptr<GameObject> GameObject::FindChild(GameObject* child)
{
	for (auto GO = children.begin(); GO != children.end(); ++GO) {
		if ((*GO).get() == child) {
			return move(*GO);
		}
	}

	return nullptr;
}

Component* GameObject::AddComponent(ComponentType type)
{
	unique_ptr<Component> newComponent;

	switch (type)
	{
	case ComponentType::TRANSFORM:
		newComponent = make_unique<TransformComponent>();
		break;
	case ComponentType::MESH:
		newComponent = make_unique<MeshComponent>();
		break;
	case ComponentType::TEXTURE:
		newComponent = make_unique<TextureComponent>();
		break;
	case ComponentType::CAMERA:
		newComponent = make_unique<CameraComponent>();
		break;
	default:
		break;
	}

	Component* retComponent = newComponent.get();

	components.push_back(move(newComponent));

	return retComponent;
}

void GameObject::AddMeshWithTexture(std::vector<Mesh::Ptr> meshes)
{
	if (meshes.size() == 1) {
		if (GetComponent<MeshComponent>() == nullptr) {
			AddComponent(MESH);
		}
		if (GetComponent<TextureComponent>() == nullptr) {
			AddComponent(TEXTURE);
		}
		MeshComponent* mesh = GetComponent<MeshComponent>();
		mesh->setMesh(*meshes.begin());
		TextureComponent* texture = GetComponent<TextureComponent>();
		texture->setTexture((*meshes.begin())->texture);
	}
	else {
		for (auto i = meshes.begin(); i != meshes.end(); ++i) {
			GameObject* GOPart = AddNewChildren(OBJECT);
			MeshComponent* meshPart = GOPart->GetComponent<MeshComponent>();
			meshPart->setMesh(*i);
			TextureComponent* texturePart = GOPart->GetComponent<TextureComponent>();
			texturePart->setTexture((*i)->texture);
		}
	}
}

void GameObject::AddMeshWithTexture(Mesh::Ptr meshes)
{
	if (GetComponent<MeshComponent>() == nullptr) {
		AddComponent(MESH);
	}
	if (GetComponent<TextureComponent>() == nullptr) {
		AddComponent(TEXTURE);
	}
	MeshComponent* mesh = GetComponent<MeshComponent>();
	mesh->setMesh(meshes);
	TextureComponent* texture = GetComponent<TextureComponent>();
	texture->setTexture(meshes->texture);
}

void GameObject::Render()
{
	bool toRender = true;
	// get necessary components
	TransformComponent* transform = GetComponent<TransformComponent>();
	if (GetComponent<MeshComponent>() == nullptr) {
		toRender = false;
	}

	glPushMatrix();
	glMultMatrixd(&transform->getTransform()[0].x);

	if (toRender) {
		MeshComponent* mesh = GetComponent<MeshComponent>();
		if (mesh->getMesh()) mesh->getMesh()->draw();
	}

	// render
	for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		(*childIt)->Render();
	}

	glPopMatrix();

}
