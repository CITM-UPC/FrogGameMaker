#include "GameApp.h"
#include <GL\glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <IL/il.h>

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
    AddLog("IL Init");
    actualCamera = new Camera();

    scene = new Scene("TestScene");
}

GameApp::~GameApp()
{
    delete actualCamera;
}

void GameApp::EditorStart() {
    // scene->DebugStart();
    house = scene->AddGameObject();
    auto mesh_ptrs = Mesh::loadFromFile("Assets\\BakerHouse.fbx", "Assets\\Baker_house.png");
    house->AddMeshWithTexture(mesh_ptrs);

    AddLog("BakerHouse.fbx loaded");

    TransformComponent* transformHouse = house->GetComponent<TransformComponent>();
    transformHouse->rotate(1, vec3(0, 1, 0));
    transformHouse->translate(vec3(0, 0, 0));
    transformHouse->scale(vec3(1, 1, 1));

}

void GameApp::EditorStep(std::chrono::duration<double> dt)
{

}

void GameApp::GameStart()
{

}

void GameApp::GameStep(std::chrono::duration<double> dt)
{
    TransformComponent* transformHouse = house->GetComponent<TransformComponent>();
    transformHouse->rotate(1, vec3(0, 1, 0));

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

    scene->Render();

#pragma endregion


    assert(glGetError() == GL_NONE);
}

void GameApp::CleanUp()
{
    // memory leaks --TODO--
    scene->CleanUp();
}

void GameApp::AddLog(string l)
{
    logs.push_back(l);
}

vector<string> GameApp::GetLogs()
{
    return logs;
}

void GameApp::ClearLogs()
{
    logs.clear();
}

