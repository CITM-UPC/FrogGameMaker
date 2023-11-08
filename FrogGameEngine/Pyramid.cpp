#include "Pyramid.h"
#include <GL/glew.h>
#include <array>
#include <vector>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

Pyramid::Pyramid() :
	a(-0.866, 0, -1),
	b(-0.866, 0, 1),
	c(0.866, 0, 0),
	d(0, 1.633, 0),
	red(1, 0, 0),
	green(0, 1, 0),
	blue(0, 0, 1),
	yellow(1, 1, 0),
	white(0, 1, 1),
	black(1, 0, 1)
{
	array<vec3, NUM_VERTEXS> vertex_data = {
		a, b, c,
		a, b, d,
		a, c, d,
		b, c, d
	};

	array<vec3, NUM_VERTEXS> color_data = {
		red,red,red,
		green,green,green,
		blue,blue,blue,
		yellow,yellow,yellow
	};

	vector<vec3> interleaved_data;
	for (size_t i = 0; i < vertex_data.size(); ++i) {
		interleaved_data.push_back(vertex_data[i]);
		interleaved_data.push_back(color_data[i]);
	}

	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * interleaved_data.size(), interleaved_data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Pyramid::Pyramid(const std::string& path) :
	a(-0.866, 0, -1),
	b(-0.866, 0, 1),
	c(0.866, 0, 0),
	d(0, 1.633, 0),
	red(1, 0, 0),
	green(0, 1, 0),
	blue(0, 0, 1),
	yellow(1, 1, 0),
	white(0, 1, 1),
	black(1, 0, 1)
{
}

void Pyramid::loadTextureToMesh(const std::string& path)
{
	aiString aiPath(path);
	fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
	auto texture_ptr = make_shared<Texture2D>(texPath.string());
	texture = texture_ptr;
}

void Pyramid::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glVertexPointer(3, GL_DOUBLE, sizeof(vec3) * 2, nullptr);
	glColorPointer(3, GL_DOUBLE, sizeof(vec3) * 2, (void*)sizeof(vec3));
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Pyramid::~Pyramid()
{
	glDeleteBuffers(1, &_buffer_id);
}
