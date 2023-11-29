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
