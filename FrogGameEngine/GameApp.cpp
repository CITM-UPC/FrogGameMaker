#include "GameApp.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

inline void GameApp::Step(std::chrono::duration<double> dt)
{
}

void GameApp::Render(RenderModes renderMode)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(camera.fov, camera.aspect, camera.zNear, camera.zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.x, camera.up.y, camera.up.z);

    /*if (renderMode == RenderModes::DEBUG) {
        drawGrid(100, 1);
        drawAxis();
    }*/
}
