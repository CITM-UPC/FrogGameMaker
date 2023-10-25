#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addChild(GraphicObject* child)
{
	_children.insert(child);
}

void Scene::removeChild(GraphicObject* child)
{
	_children.erase(child);
}
