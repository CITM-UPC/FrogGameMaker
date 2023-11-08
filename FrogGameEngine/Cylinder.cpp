#include "Cylinder.h"
#include <GL/glew.h>
#include <array>
#include <vector>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

Cylinder::Cylinder() :
	a(0, 0, 0),
	b(1, 0, 0),
	c(0.707, 0, 0.707),
	d(0, 0, 1),
	e(-0.707, 0, 0.707),
	f(-1, 0, 0),
	g(-0.707, 0, -0.707),
	h(0, 0, -1),
	i(0.707, 0, -0.707),
	j(0, 2, 0),
	k(1, 2, 0),
	l(0.707, 2, 0.707),
	m(0, 2, 1),
	n(-0.707, 2, 0.707),
	o(-1, 2, 0),
	p(-0.707, 2, -0.707),
	q(0, 2, -1),
	r(0.707, 2, -0.707),
	red(1, 0, 0),
	green(0, 1, 0),
	blue(0, 0, 1),
	yellow(1, 1, 0),
	white(0, 1, 1),
	black(1, 0, 1)
{
	array<vec3, NUM_VERTEXS> vertex_data = {
		a, b, c,
		a, c, d,
		a, d, e,
		a, e, f,
		a, f, g, 
		a, g, h, 
		a, h, i, 
		a, i, b, 

		b, c, k, 
		c, k, l,
		c, d, l, 
		d, l, m,
		d, e, m, 
		e, m, n,
		e, f, n, 
		f, n, o,
		f, g, o,
		g, o, p, 
		g, h, p, 
		h, p, q, 
		h, i, q, 
		i, q, r, 
		i, b, r, 
		b, r, k,

		j, k, l, 
		j, l, m, 
		j, m, n, 
		j, n, o, 
		j, o, p,
		j, p, q, 
		j, q, r, 
		j, r, k
	};

	array<vec3, NUM_VERTEXS> color_data = {
		white,white,white,
		white,white,white,
		white,white,white,
		white,white,white,
		white,white,white,
		white,white,white,
		white,white,white,
		white,white,white,
		red,red,red,
		red,red,red,
		green,green,green,
		green,green,green,
		blue,blue,blue,
		blue,blue,blue,
		yellow,yellow,yellow,
		yellow,yellow,yellow,
		red,red,red,
		red,red,red,
		green,green,green,
		green,green,green,
		blue,blue,blue,
		blue,blue,blue,
		yellow,yellow,yellow,
		yellow,yellow,yellow,
		black,black,black,
		black,black,black,
		black,black,black,
		black,black,black,
		black,black,black,
		black,black,black,
		black,black,black,
		black,black,black,
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

void Cylinder::draw()
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

Cylinder::~Cylinder()
{
	glDeleteBuffers(1, &_buffer_id);
}
