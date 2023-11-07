#pragma once

#include "Types.h"
#include "Graphic.h"
#include "Texture2D.h"
#include <array>

struct Cube : Graphic
{
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

struct CubeImmediateMode : public Cube
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

class CubeVertexArray : public Cube
{
	std::array<vec3, NUM_VERTEXS> _vertex_data;
	std::array<vec3, NUM_VERTEXS> _color_data;

public:
	CubeVertexArray();
	void draw();
};

class CubeVertexBuffer : public Cube
{

	unsigned int _vertex_buffer_id;
	unsigned int _color_buffer_id;

public:
	CubeVertexBuffer();
	void draw();

};

class CubeWireframeIVBO : public Cube
{
	unsigned int _buffer_id;
	unsigned int _index_bufer_id;

public:
	CubeWireframeIVBO();
	void draw();
	~CubeWireframeIVBO();

};