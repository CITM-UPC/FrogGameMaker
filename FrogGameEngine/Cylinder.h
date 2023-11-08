#pragma once

#include "Types.h"
#include "Graphic.h"
#include "Texture2D.h"
#include <array>

class Cylinder : public Graphic
{
	const vec3 a;
	const vec3 b;
	const vec3 c;
	const vec3 d;
	const vec3 e;
	const vec3 f;
	const vec3 g;
	const vec3 h;
	const vec3 i;
	const vec3 j;
	const vec3 k;
	const vec3 l;
	const vec3 m;
	const vec3 n;
	const vec3 o;
	const vec3 p;
	const vec3 q;
	const vec3 r;

	const vec3 red;
	const vec3 green;
	const vec3 blue;
	const vec3 yellow;
	const vec3 white;
	const vec3 black;

public:
	unsigned int _buffer_id;

	static const int NUM_FACES = 10;
	static const int NUM_TRIANGLES = (NUM_FACES-2) * 2 + 2 * (NUM_FACES - 2) ;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;


	Cylinder();

	void draw();

	~Cylinder();
};

