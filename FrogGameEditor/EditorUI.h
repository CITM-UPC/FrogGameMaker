#pragma once

#include "EditorModule.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "EditorWindow.h"

#include "../FrogGameEngine/GameApp.h"

#include "../FrogGameEngine/GraphicObject.h"

#include "assimp/version.h"

#include "IL/il.h"

#include "../FrogGameEngine/Mesh.h"
#include "../FrogGameEngine/Cube.h"
#include "../FrogGameEngine/Pyramid.h"
#include "../FrogGameEngine/Cylinder.h"


class EditorUI : public EditorModule {
public:
	EditorUI();

	// TODO: change window and gl_context to pick it from app
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:
	bool dockSpaceEnabled;

	bool editorActivated;

	bool quitPressed;

	bool showDemoWindow;
	bool showAnotherWindow;

	bool showHardwareWindow;
	bool showAboutPopup;
	bool showFPSLog;

	bool showConfigWindow;

	bool showHierarchyWindow;
	bool showInspectorWindow;

	bool showConsoleWindow;
	bool showAssetsWindow;
	
	GameObject* gameObjectSelected = nullptr;

	ImVec4 clearColor;

private:
	void UIMainMenuBar();

	void UIAboutPopup();
	void UIHardwareWindow();
	void UIFPSLog();

	void UIConfigWindowWindow();
	void UIConfigRendererWindow();
	void UIConfigInputWindow();

	void UIHierarchyNodeWrite(GameObject* GO);
	void UIHierarchyWindow();

	void UIInspectorWriteTransformNode(Component* component);
	void UIInspectorWriteMeshNode(Component* component);
	void UIInspectorWriteTextureNode(Component* component);
	void UIInspectorNodeWrite(Component* component);
	void UIInspectorWindow();

	void UIConsoleWindow();
	void UIAssetsWindow();

};