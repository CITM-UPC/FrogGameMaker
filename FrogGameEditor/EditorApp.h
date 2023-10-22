#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <list>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "EditorModule.h"

#include "../FrogGameEngine/GameApp.h"

using namespace std;
using namespace chrono;

static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

class EditorInput;
class EditorWindow;
class EditorUI;

class EditorApp
{
public:
	EditorApp();
	~EditorApp();

	bool Start();

	bool Update();

	bool Cleanup();

	//// use this before the game render to get all the info into the BFO to then pass it to the UI
	//void PreGameAppRender();

	//// use this after the game render to finish the BFO
	//void PostGameAppRender();

	EditorInput* editorInput;
	EditorWindow* editorWindow;
	EditorUI* editorUI;

	list<EditorModule*> modules;

	vector<float> FPS_Log;

	GameApp* gameApp;

	/*GLuint gameAppRenderFBO;

	GLuint gameAppRenderTexture;*/

private:

};
