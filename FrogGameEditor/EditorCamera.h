#pragma once
#include "EditorModule.h"

#include "../FrogGameEngine/GameRenderer.h"

class EditorCamera : public EditorModule {
public:
	EditorCamera();

	bool Start();
	bool Update();

	void TranslateLocally(vec3 translation);
	void OrbitAround(vec2 motion);
	void LookAround(vec2 motion);
	void CameraZoom(double amount);
	void FocusOn(vec3 focusPoint);

	float baseSpeed = 0.15;

	// if the mouse pressed is drag to ui this still is false
	bool mouseOnUI;

	Camera camera;
};