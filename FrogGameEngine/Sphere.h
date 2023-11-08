#pragma once

#include "Types.h"
#include "Graphic.h"
#include "Texture2D.h"
#include <array>
#include <vector>

class Sphere : public Graphic
{
	float radius;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> lineIndices;

	std::vector<float> interleavedVertices;
	int interleavedStride;

public:

	static const int NUM_SLICE = 18;
	static const int NUM_STACK = 10;
	static const int NUM_TRIANGLES = NUM_SLICE *(NUM_STACK - 2) + NUM_STACK*2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;

	void BuildVertices();

	Sphere();

	void draw();

	~Sphere();

};

