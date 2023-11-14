#pragma once
#include <iostream>

#include "EditorModule.h"

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "EditorUI.h"
#include <filesystem>

#define MAX_KEYS 300
#define NUM_MOUSE_BUTTONS 5

enum KeyState {
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class EditorInput : public EditorModule {
public:
	EditorInput();
	~EditorInput();

	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

	KeyState GetKey(int id) const {
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const {
		return mouseButtons[id - 1];
	}

	vec2 GetMouseMotion() const {
		return vec2(mouseMotionX, mouseMotionY);
	}

	int GetMouseWheelScroll() const {
		return mouseWheelScroll;
	}

	bool WindowSizeHasUpdated() const {
		return windowSizeHasUpdated;
	}

private:
	KeyState* keyboard;
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];

	int	mouseMotionX;
	int mouseMotionY;

	int	mouseWheelScroll;

	bool windowSizeHasUpdated;
};

