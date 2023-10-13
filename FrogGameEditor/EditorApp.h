#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>



#include "EditorWindow.h"

#include "../FrogGameEngine/GameApp.h"



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
	editorWindow = new EditorWindow();



	gameApp = new GameApp();
}

EditorApp::~EditorApp()
{
}

bool EditorApp::Start() {

	

	// module start
	{
		editorWindow->Start();


	}

	return true;
}

bool EditorApp::Update() {

	// pre update
	{
		editorWindow->PreUpdate();

	}

	// update
	{
		editorWindow->Update();

	}

	// post update
	{
		editorWindow->PostUpdate();

	}

	return true;
}

bool EditorApp::Cleanup() {





	
	return true;
}