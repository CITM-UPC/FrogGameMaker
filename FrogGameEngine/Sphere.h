#pragma once
#include "Graphic.h"
class Sphere : public Graphic
{
public:
	Sphere();

	void draw();
public:
	float radius;
};

