#pragma once
#include <iostream>

#include "EditorModule.h"

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "EditorUI.h"

class EditorInput : public EditorModule
{
public:
	EditorInput(EditorApp* editor);
	~EditorInput();

	bool Start();

	bool PreUpdate();

	bool Update();

	bool PostUpdate();

	bool CleanUp();

private:

};

EditorInput::EditorInput(EditorApp* editor) : EditorModule(editor)
{
}

EditorInput::~EditorInput()
{
}

bool EditorInput::Start() {

	return true;
}

bool EditorInput::PreUpdate() {

	char* dropped_filedir;

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
		case (SDL_DROPFILE): {      // In case if dropped file
			dropped_filedir = event.drop.file;
			// Shows directory of dropped file
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_INFORMATION,
				"File dropped on window",
				dropped_filedir,
				editor->editorWindow->window
			);
			SDL_free(dropped_filedir); }   // Free dropped_filedir memory
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

	return true;
}