#pragma once

#include "Types.h"
#include "Graphic.h"
#include "Texture2D.h"
#include <array>

class Cube : public Graphic {

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


public:
	unsigned int _buffer_id;

	static const int NUM_FACES = 6;
	static const int NUM_TRIANGLES = NUM_FACES * 2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;


	Cube();
	Cube(const std::string& path);

	void loadTextureToMesh(const std::string& path);
	Texture2D::Ptr texture;

	Texture2D::Ptr checkboard = std::shared_ptr<Texture2D>(new Texture2D);
	bool drawChecker = false;

	void draw();

	~Cube();


};


