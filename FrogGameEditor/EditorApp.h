#pragma once
#include "../FrogGameEngine/GameApp.h"
#include "EditorWindow.h"
class EditorApp
{
public:
	EditorApp();
	~EditorApp();

	bool Start();

	bool Update();

	bool Cleanup();

	GameApp* gameApp;

	EditorWindow* editorWindow;
private:

};

EditorApp::EditorApp()
{
}

EditorApp::~EditorApp()
{
}

bool EditorApp::Start() {

	return true;
}

bool EditorApp::Update() {

	return true;
}

bool EditorApp::Cleanup() {

	return true;
}