#pragma once

#include "Types.h"
#include "Graphic.h"
#include <glm/ext/matrix_transform.hpp>
#include <set>
#include <memory>

class GraphicObject
{
public:
	mat4 _transform;
	std::set<GraphicObject*> _children;
	GraphicObject* _parent;
	std::shared_ptr<Graphic> _graphic;

public:
	GraphicObject();
	GraphicObject(std::shared_ptr<Graphic> graphic);

	inline vec3& pos() { return (vec3&)(_transform[3]); }
	inline void rotate(double rads, const vec3& axis) { _transform = glm::rotate(_transform, rads, axis); }

	void paint();

	void addChild(GraphicObject* child);
	void removeChild(GraphicObject* child);

	virtual ~GraphicObject();

private:
	GraphicObject(const GraphicObject&);
	GraphicObject& operator=(const GraphicObject&);
};
