#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(string name)
{
	this->name = name;
}

Scene::~Scene()
{
}

GameObject* Scene::AddGameObject()
{
	string gameObjectName = "Game Object " + std::to_string(children.size());

	unique_ptr<GameObject> ptrGameObject = make_unique<GameObject>(gameObjectName);
	GameObject* copyGameObject = ptrGameObject.get();

	children.push_back(move(ptrGameObject));

	return copyGameObject;
}

GameObject* Scene::AddGameObject(string name)
{
	unique_ptr<GameObject> ptrGameObject = make_unique<GameObject>(name);
	GameObject* copyGameObject = ptrGameObject.get();

	children.push_back(move(ptrGameObject));

	return copyGameObject;
}

GameObject* Scene::AddGameObjectChildren(GameObject* parent)
{
	string gameObjectName = parent->name + " " + std::to_string(parent->children.size());

	unique_ptr<GameObject> ptrGameObject = make_unique<GameObject>(gameObjectName);
	GameObject* copyGameObject = ptrGameObject.get();

	parent->AddChild(move(ptrGameObject));

	return copyGameObject;

}

unique_ptr<GameObject> Scene::FindChild(GameObject* child)
{
	for (auto GO = children.begin(); GO != children.end(); ++GO) {
		if ((*GO).get() == child) {
			return move(*GO);
		}
	}

	return nullptr;
}

void Scene::MoveChildToAnotherParent(GameObject* child, GameObject* toParent)
{
	list<unique_ptr<GameObject>>::iterator GO;
	
	// if the child has a parent, look in the parent children, if not, look at the scene children
	if (child->_parent != nullptr) {
		for (GO = child->_parent->children.begin(); GO != child->_parent->children.end(); ++GO) {
			if ((*GO).get() == child) {
				break;
			}
		}
		if (toParent != nullptr) {
			toParent->children.splice(toParent->children.begin(), child->_parent->children, GO);
			child->_parent = toParent;
		}
		else {
			children.splice(children.begin(), child->_parent->children, GO);
			child->_parent = nullptr;
		}
	}
	else {
		for (GO = children.begin(); GO != children.end(); ++GO) {
			if ((*GO).get() == child) {
				break;
			}
		}
		if (toParent != nullptr) {
			toParent->children.splice(toParent->children.begin(), children, GO);
			child->_parent = toParent;
		}
		else {
			children.splice(children.begin(), children, GO);
			child->_parent = nullptr;
		}
	}


	
}

void Scene::DebugStart()
{
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
}

void Scene::Start()
{
}

void Scene::Update()
{
}

void Scene::Render()
{
	for (auto gameObjectI = children.begin(); gameObjectI != children.end(); ++gameObjectI) {
		(*gameObjectI)->Render();
	}

}

void Scene::CleanUp()
{
	children.clear();
}
