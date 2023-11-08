#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Graphic.h"
#include "Texture2D.h"
#include "Types.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"

class Mesh :
    public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; }; //Vector 3 points
	struct V3C4 { vec3f v; vec4f c; }; //Vector 3 points, color
	struct V3T2 { vec3f v; vec2f t; }; //Vector 3 points, texture 2D

private:
	const enum Formats _format;

	unsigned int _vertex_buffer_id;
	const unsigned int _numVerts;

	unsigned int _indexs_buffer_id;
	const unsigned int _numIndexs;

public:
	using Ptr = std::shared_ptr<Mesh>;

	static std::vector<Ptr> loadFromFile(const std::string& path);
	static std::vector<Ptr> loadFromFile(const std::string& path, const std::string& stringPath);

	std::string path;
	
	void loadTextureToMesh(const std::string& path);
	Texture2D::Ptr texture;

	Texture2D::Ptr checkboard = std::shared_ptr<Texture2D>(new Texture2D);
	bool drawChecker = false;

	virtual Mesh();
	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data = nullptr, unsigned int numIndexs = 0);
	Mesh(Mesh&& b) noexcept;
	void draw();
	~Mesh();

private:
	Mesh(const Mesh& cpy);
	Mesh& operator=(const Mesh&);

};

