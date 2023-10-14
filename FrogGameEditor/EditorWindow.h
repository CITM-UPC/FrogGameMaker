#pragma once
#include <iostream>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

static const unsigned int WINDOW_WIDTH = 720 * 16 / 9;
static const unsigned int WINDOW_HEIGHT = 720;

using namespace std;
using namespace chrono;


static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;
class EditorWindow
{
public:
	EditorWindow();
	~EditorWindow();

	bool Start();

	bool PreUpdate();

	bool Update();

	bool PostUpdate();

	bool CleanUp();


	SDL_Window* window;

	SDL_GLContext glContext;

};

EditorWindow::EditorWindow()
{
}

EditorWindow::~EditorWindow()
{
}

bool EditorWindow::Start() {

	// setup SDL window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// GL 3.1 + GLSL 130
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	window = SDL_CreateWindow("SDL+OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (!window) 
		throw exception(SDL_GetError());

	glContext = SDL_GL_CreateContext(window);
	if (!glContext) 
		throw exception(SDL_GetError());

	if (SDL_GL_MakeCurrent(window, glContext) != 0) 
		throw exception(SDL_GetError());

	if (SDL_GL_SetSwapInterval(1) != 0) 
		throw exception(SDL_GetError());

	// init opengl
	auto glew_init_error = glewInit();
	if (glew_init_error != GLEW_OK) 
		throw exception((char*)glewGetErrorString(glew_init_error));
	if (!GLEW_VERSION_3_1) 
		throw exception("OpenGL 3.1 Not Supported!");

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}

bool EditorWindow::PreUpdate() {


	return true;
}

bool EditorWindow::Update() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	return true;
}

bool EditorWindow::PostUpdate() {


	SDL_GL_SwapWindow(window);

	return true;
}

bool EditorWindow::CleanUp() {

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return true;
}