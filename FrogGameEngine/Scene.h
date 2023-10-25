#pragma once
#include "GraphicObject.h"
class Scene
{
public:
	Scene();
	~Scene();

	std::set<GraphicObject*> _children;

	void addChild(GraphicObject* child);
	void removeChild(GraphicObject* child);

};

