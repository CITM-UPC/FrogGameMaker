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

	GameObject* tempGO = new GameObject(gameObjectName);
	children.push_back(tempGO);
	return tempGO;
}

GameObject* Scene::AddGameObject(string name)
{
	GameObject* tempGO = new GameObject(name);
	children.push_back(tempGO);
	return tempGO;

}

GameObject* Scene::AddGameObjectChildren(GameObject* parent)
{
	string gameObjectName = parent->name + " " + std::to_string(parent->children.size());

	GameObject* tempGO = new GameObject(gameObjectName);
	parent->addChild(tempGO);
	return tempGO;

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
