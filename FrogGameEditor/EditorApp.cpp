#include "EditorApp.h"

#include "EditorWindow.h"
#include "EditorInput.h"
#include "EditorUI.h"

EditorApp::EditorApp()
{
	editorInput = new EditorInput(this);
	editorWindow = new EditorWindow(this);
	editorUI = new EditorUI(this);

	modules.push_back(editorInput);
	modules.push_back(editorWindow);
	modules.push_back(editorUI);


	gameApp = new GameApp();
}

EditorApp::~EditorApp()
{
}

bool EditorApp::Start() {

	bool ret = true;

	// sdl init
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw exception(SDL_GetError());

	SDL_version compiled;
	SDL_VERSION(&compiled);
	cout << "SDL Compiled with " << to_string(compiled.major) << '.' << to_string(compiled.minor) << '.' << to_string(compiled.patch);

	SDL_version linked;
	SDL_GetVersion(&linked);
	cout << "SDL Linked with " << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch);

	// module start
	{
		auto item = modules.begin();

		while (item != modules.end() && ret == true) {
			ret = (*item)->Start();
			++item;
		}
	}

	return ret;
}

bool EditorApp::Update() {

	const auto frame_start = steady_clock::now();

	bool ret = true;

	// pre update
	{
		auto item = modules.begin();

		while (item != modules.end() && ret == true) {
			ret = (*item)->PreUpdate();
			++item;
		}
	}

	// update
	{
		auto item = modules.begin();

		while (item != modules.end() && ret == true) {
			ret = (*item)->Update();
			++item;
		}

		gameApp->Step(FDT);
	}

	// post update
	{
		gameApp->Render(GameApp::RenderModes::DEBUG);

		auto item = modules.begin();

		while (item != modules.end() && ret == true) {
			ret = (*item)->PostUpdate();
			++item;
		}

		editorWindow->Render();
	}

	const auto frame_end = steady_clock::now();
	const auto frame_duration = frame_end - frame_start;
	if (frame_duration < FDT)
		this_thread::sleep_for(FDT - frame_duration);

	return ret;
}

bool EditorApp::Cleanup() {

	editorUI->CleanUp();
	editorInput->CleanUp();
	editorWindow->CleanUp();

	SDL_Quit();

	return true;
}