#pragma once
#include "EditorModule.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "../FrogGameEngine/GameObject.h"

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

	void UIInspectorWriteTransformNode(TransformComponent* component);
	void UIInspectorWriteMeshNode(MeshComponent* component);
	void UIInspectorWriteTextureNode(TextureComponent* component);
	void UIInspectorWriteCameraNode(CameraComponent* component);
	void UIInspectorNodeWrite(Component* component);
	void UIInspectorWindow();

	void UIConsoleWindow();
	void UIAssetsWindow();

};