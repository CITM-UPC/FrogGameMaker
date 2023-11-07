#pragma once

#include "Types.h"
#include "Graphic.h"
#include "Texture2D.h"
#include <array>

class Cube : public Graphic {
	enum Format {
		INMIDIATEMODE,
		INTERLEAVEDVBO,
		VERTEXBUFFER
	};

public:
	static const int NUM_FACES = 6;
	static const int NUM_TRIANGLES = NUM_FACES * 2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;

	const vec3 a;
	const vec3 b;
	const vec3 c;
	const vec3 d;
	const vec3 e;
	const vec3 f;
	const vec3 g;
	const vec3 h;

	const vec3 red;
	const vec3 green;
	const vec3 blue;
	const vec3 yellow;
	const vec3 white;
	const vec3 black;

	Cube();
};

class CubeImmediateMode : public Cube
{
	Texture2D texture;
	void draw();

	CubeImmediateMode();
};

class CubeInterleavedVBO : public Cube
{

	unsigned int _buffer_id;

public:
	CubeInterleavedVBO();
	void draw();

	~CubeInterleavedVBO();

};

class CubeVertexBuffer : public Cube
{

	unsigned int _vertex_buffer_id;
	unsigned int _color_buffer_id;

public:
	CubeVertexBuffer();
	void draw();

};
