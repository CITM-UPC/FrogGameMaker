#pragma once
#include "EditorModule.h"

#include "../FrogGameEngine/GameRenderer.h"

class EditorCamera : public EditorModule {
public:
	EditorCamera(EditorApp* editor) : EditorModule(editor) {

	};

	bool Update() {
		if (editor->editorInput->GetKey(SDL_SCANCODE_W)) {
			camera.eye += vec3(0, 0, -speed);
			camera.center += vec3(0, 0, -speed);
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_S)) {
			camera.eye += vec3(0, 0, speed);
			camera.center += vec3(0, 0, speed);
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_SPACE)) {
			camera.eye += vec3(0, speed, 0);
			camera.center += vec3(0, speed, 0);
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_LSHIFT)) {
			camera.eye += vec3(0, -speed, 0);
			camera.center += vec3(0, -speed, 0);
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_A)) {
			camera.eye += vec3(-speed, 0, 0);
			camera.center += vec3(-speed, 0, 0);
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_D)) {
			camera.eye += vec3(speed, 0, 0);
			camera.center += vec3(speed, 0, 0);
		}

		return true;
	}

	void TranslateLocally(vec3 translation) {

	}

	float speed = 0.5;

	Camera camera;
};