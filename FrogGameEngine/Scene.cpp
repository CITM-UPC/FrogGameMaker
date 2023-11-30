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

	children.push_back(make_unique<GameObject>(gameObjectName));
	return children.back().get();
}

GameObject* Scene::AddGameObject(string name)
{
	children.push_back(make_unique<GameObject>(name));
	return children.back().get();
}

GameObject* Scene::AddGameObjectChildren(GameObject* parent)
{
	string gameObjectName = parent->name + " " + std::to_string(parent->children.size());

	parent->AddChild(make_unique<GameObject>(gameObjectName));
	return parent->children.back().get();

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
