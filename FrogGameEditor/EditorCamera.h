#pragma once
#include "EditorApp.h"
#include "EditorInput.h"

#include "../FrogGameEngine/GameRenderer.h"

struct EditorCamera : public Camera {
	EditorCamera(EditorApp* editor) {
		this->editor = editor;
	}

	//void Update() {

	//	switch ()


	//}

	EditorApp* editor = nullptr;

};