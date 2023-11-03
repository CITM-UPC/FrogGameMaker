#include "GameApp.h"
#include <GL\glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <IL/il.h>

#include "Mesh.h"

#include "GraphicObject.h"

using namespace std;

static double angle = 0.0;

static void drawAxis() {
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0.8, 0, 0);
    glColor3ub(0, 255, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0.8, 0);
    glColor3ub(0, 0, 1);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 0.8);
    glEnd();
}

static void drawGrid(int grid_size, int grid_step) {
    glLineWidth(1.0);
    glColor3ub(128, 128, 128);

    glBegin(GL_LINES);
    for (int i = -grid_size; i <= grid_size; i += grid_step) {
        //XY plane
        glVertex2i(i, -grid_size);
        glVertex2i(i, grid_size);
        glVertex2i(-grid_size, i);
        glVertex2i(grid_size, i);

        //XZ plane
        glVertex3i(i, 0, -grid_size);
        glVertex3i(i, 0, grid_size);
        glVertex3i(-grid_size, 0, i);
        glVertex3i(grid_size, 0, i);
    }
    glEnd();
}

GameApp::GameApp()
{
    ilInit();
    actualCamera = new Camera();
}

GameApp::~GameApp()
{
    delete actualCamera;
}

void GameApp::Step(std::chrono::duration<double> dt)
{
    const double angle_vel = 90.0; // degrees per second
    angle += angle_vel * dt.count();
}

void GameApp::Render(Camera camera) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.fov, camera.aspect, camera.zNear, camera.zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.x, camera.up.y, camera.up.z);

    drawGrid(100, 1);
    drawAxis();

#pragma region Draw Sandbox
    static auto mesh_ptrs = Mesh::loadFromFile("Assets/BakerHouse.fbx");

    GraphicObject mesh1(mesh_ptrs.front());
    GraphicObject mesh2(mesh_ptrs.back());

    GraphicObject house;

    house.addChild(std::move(mesh1));
    house.addChild(std::move(mesh2));

    GraphicObject root;
    root.addChild(std::move(house));

    root.paint();

#pragma endregion


    assert(glGetError() == GL_NONE);
}

