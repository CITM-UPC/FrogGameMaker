#include "Cube.h"
#include <GL/glew.h>
#include <array>
#include <vector>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;


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
    black(1, 0, 1)
{
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

Cube::Cube(const std::string& path) :
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
    black(1, 0, 1)
{
    aiString aiPath(path);
    fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
    auto texture_ptr = make_shared<Texture2D>(texPath.string());
    texture = texture_ptr;
}

void Cube::loadTextureToMesh(const std::string& path)
{
    aiString aiPath(path);
    fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
    auto texture_ptr = make_shared<Texture2D>(texPath.string());
    texture = texture_ptr;
}

void Cube::draw()
{
    glEnable(GL_TEXTURE_2D);
    if (texture.get() && drawChecker == false)
    {
        texture->bind();
    }
    else if (drawChecker){
        checkboard.get()->bind();
    }
    else {
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

    glColor4ub(255, 255, 255, 255);

    glBegin(GL_TRIANGLES);
    //front
    drawQuadFaceTriangles(a, b, c, d);
    //back
    drawQuadFaceTriangles(h, g, f, e);
    //left
    drawQuadFaceTriangles(e, a, d, h);
    //right
    drawQuadFaceTriangles(b, f, g, c);
    //top
    drawQuadFaceTriangles(d, c, g, h);
    //bottom
    drawQuadFaceTriangles(b, a, e, f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

Cube::~Cube()
{

}




