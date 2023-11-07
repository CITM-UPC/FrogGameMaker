#include "Cube.h"
#include <GL/glew.h>
#include <array>
#include <vector>

using namespace std;

Cube::Cube() :
    a(-1, -1, 1),
    b(1, -1, 1),
    c(1, 1, 1),
    d(-1, 1, 1),
    e(-1, -1, -1),
    f(1, -1, -1),
    g(1, 1, -1),
    h(-1, 1, -1),
    red(1, 0, 0),
    green(0, 1, 0),
    blue(0, 0, 1),
    yellow(1, 1, 0),
    white(0, 1, 1),
    black(1, 0, 1) {
}

//Cube immediate mode

static void drawQuadFaceTriangles(vec3 a, vec3 b, vec3 c, vec3 d) {
    glTexCoord2d(0, 1);
    glVertex3dv(&a.x);
    glTexCoord2d(1, 1);
    glVertex3dv(&b.x);
    glTexCoord2d(1, 0);
    glVertex3dv(&c.x);

    glTexCoord2d(1, 0);
    glVertex3dv(&c.x);
    glTexCoord2d(0, 0);
    glVertex3dv(&d.x);
    glTexCoord2d(0, 1);
    glVertex3dv(&a.x);
}

CubeImmediateMode::CubeImmediateMode() : texture("Lenna.png") {}

void CubeImmediateMode::draw() {

    glEnable(GL_TEXTURE_2D);
    texture.bind();

    glColor4ub(255, 255, 255, 255);

    glBegin(GL_TRIANGLES);
    //front
    //glColor3dv(&red.x);
    drawQuadFaceTriangles(a, b, c, d);
    //back
    //glColor3dv(&green.x);
    drawQuadFaceTriangles(h, g, f, e);
    //left
    //glColor3dv(&blue.x);
    drawQuadFaceTriangles(e, a, d, h);
    //right
    //glColor3dv(&yellow.x);
    drawQuadFaceTriangles(b, f, g, c);
    //top
    //glColor3dv(&white.x);
    drawQuadFaceTriangles(d, c, g, h);
    //bottom
    //glColor3dv(&black.x);
    drawQuadFaceTriangles(b, a, e, f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

//Cube interleaved VBO

CubeInterleavedVBO::CubeInterleavedVBO() :
    Cube() {

    array<vec3, NUM_VERTEXS> vertex_data = {
        a,b,c,c,d,a,
        h,g,f,f,e,h,
        e,a,d,d,h,e,
        b,f,g,g,c,b,
        d,c,g,g,h,d,
        b,a,e,e,f,b
    };

    array<vec3, NUM_VERTEXS> color_data = {
        red,red,red,red,red,red,
        green,green,green,green,green,green,
        blue,blue,blue,blue,blue,blue,
        yellow,yellow,yellow,yellow,yellow,yellow,
        white,white,white,white,white,white,
        black,black,black,black,black,black,
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

void CubeInterleavedVBO::draw() {
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

CubeInterleavedVBO::~CubeInterleavedVBO() {
    glDeleteBuffers(1, &_buffer_id);
}

//Cube Vertex Buffer

CubeVertexBuffer::CubeVertexBuffer() :
    Cube() {

    array<vec3, NUM_VERTEXS> vertex_data = {
        a,b,c,c,d,a,
        h,g,f,f,e,h,
        e,a,d,d,h,e,
        b,f,g,g,c,b,
        d,c,g,g,h,d,
        b,a,e,e,f,b
    };

    glGenBuffers(1, &_vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertex_data.size(), vertex_data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    array<vec3, NUM_VERTEXS> color_data = {
        red,red,red,red,red,red,
        green,green,green,green,green,green,
        blue,blue,blue,blue,blue,blue,
        yellow,yellow,yellow,yellow,yellow,yellow,
        white,white,white,white,white,white,
        black,black,black,black,black,black,
    };

    glGenBuffers(1, &_color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * color_data.size(), color_data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeVertexBuffer::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glVertexPointer(3, GL_DOUBLE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
    glColorPointer(3, GL_DOUBLE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
