#pragma once
#include <iostream>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "EditorUI.h"

class EditorInput
{
public:
	EditorInput();
	~EditorInput();

	bool Start();

	bool PreUpdate();

	bool Update();

	bool PostUpdate();

	bool CleanUp();

private:
	SDL_Window* window;

	SDL_GLContext glContext;


};

EditorInput::EditorInput()
{
}

EditorInput::~EditorInput()
{
}

bool EditorInput::Start() {

	return true;
}

bool EditorInput::PreUpdate() {

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
		case SDL_QUIT: return false;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: return false;
			}
			break;
		}
	}
	return true;
}

bool EditorInput::Update() {

	return true;
}

bool EditorInput::PostUpdate() {

	return true;
}

bool EditorInput::CleanUp() {

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return true;
}