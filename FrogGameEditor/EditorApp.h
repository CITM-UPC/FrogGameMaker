#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <list>

#include <windows.h>
#include <shellapi.h>

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
class EditorCamera;

class EditorApp
{
public:
	EditorApp();
	~EditorApp();

	bool Start();

	bool Update();

	bool Cleanup();

	void WebRequest(const char* url);

	//// use this before the game render to get all the info into the BFO to then pass it to the UI
	//void PreGameAppRender();

	//// use this after the game render to finish the BFO
	//void PostGameAppRender();

	EditorInput* editorInput;
	EditorWindow* editorWindow;
	EditorUI* editorUI;
	EditorCamera* editorCamera;

	list<EditorModule*> modules;

	vector<float> FPS_Log;

	GameApp* gameApp;

	void AddLog(string l);

	vector<string> GetLogs();

	void ClearLogs();

	/*GLuint gameAppRenderFBO;

	GLuint gameAppRenderTexture;*/

private:
	vector<string> logs;

};
