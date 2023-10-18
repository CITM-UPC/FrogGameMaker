#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "EditorWindow.h"
#include "EditorInput.h"
#include "EditorUI.h"

#include "../FrogGameEngine/GameApp.h"

static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

class EditorApp
{
public:
	EditorApp();
	~EditorApp();

	bool Start();

	bool Update();

	bool Cleanup();

	EditorWindow* editorWindow;
	EditorInput* editorInput;
	EditorUI* editorUI;

	GameApp* gameApp;

private:

};

EditorApp::EditorApp()
{
	editorWindow = new EditorWindow();
	editorInput = new EditorInput();
	editorUI = new EditorUI();

	gameApp = new GameApp();
}

EditorApp::~EditorApp()
{
}

bool EditorApp::Start() {

	// sdl init
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw exception(SDL_GetError());

	SDL_version compiled;
	SDL_VERSION(&compiled);
	cout << "SDL Compiled with " << to_string(compiled.major) << '.' << to_string(compiled.minor) << '.' << to_string(compiled.patch);

	SDL_version linked;
	SDL_GetVersion(&linked);
	cout << "SDL Linked with " << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch);

	// module start
	{
		editorWindow->Start();
		editorInput->Start();
		editorUI->Start(editorWindow->window, editorWindow->glContext);
	}

	return true;
}

bool EditorApp::Update() {

	const auto frame_start = steady_clock::now();

	// pre update
	if (editorInput->PreUpdate()) {
		{
			editorWindow->PreUpdate();
			editorInput->PreUpdate();
			editorUI->PreUpdate();
		}

		// update
		{
			editorWindow->Update();
			editorInput->Update();
			editorUI->Update();

			gameApp->Step(FDT);
		}

		// post update
		{
			editorInput->PostUpdate();
			editorUI->PostUpdate();

			gameApp->Render(GameApp::RenderModes::DEBUG);

			editorWindow->PostUpdate();

		}

		const auto frame_end = steady_clock::now();
		const auto frame_duration = frame_end - frame_start;
		if (frame_duration < FDT) 
			this_thread::sleep_for(FDT - frame_duration);

		return true;

	}
	
	return false;
}

bool EditorApp::Cleanup() {

	editorUI->CleanUp();
	editorInput->CleanUp();
	editorWindow->CleanUp();

	SDL_Quit();
	
	return true;
}