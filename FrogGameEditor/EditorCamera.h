#pragma once
#include "EditorModule.h"

#include "../FrogGameEngine/GameObject.h"

class EditorCamera : public EditorModule {
public:
	EditorCamera();

	bool Start();
	bool Update();

	void Translate(vec3 translation, ReferenceAxis ref = LOCAL);
	void OrbitAround(vec2 motion);
	void LookAround(vec2 motion);
	void CameraZoom(double amount);
	void FocusOn(vec3 focusPoint);

	float baseSpeed = 0.15;

	// if the mouse pressed is drag to ui this still is false
	bool mouseOnUI;

	vec3 focusPosition = { 0, 0, 0 };

	unique_ptr<GameObject> cameraObject;
};