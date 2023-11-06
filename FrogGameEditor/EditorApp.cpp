#include "EditorApp.h"

#include "EditorWindow.h"
#include "EditorInput.h"
#include "EditorUI.h"
#include "EditorCamera.h"

EditorApp::EditorApp()
{
	editorInput = new EditorInput(this);
	editorWindow = new EditorWindow(this);
	editorUI = new EditorUI(this);
	editorCamera = new EditorCamera(this);

	modules.push_back(editorInput);
	modules.push_back(editorWindow);
	modules.push_back(editorUI);
	modules.push_back(editorCamera);

	FPS_Log.push_back(0.0f);

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
	AddLog("SDL Compiled with " + to_string(compiled.major) + '.' + to_string(compiled.minor) + '.' + to_string(compiled.patch));

	SDL_version linked;
	SDL_GetVersion(&linked);
	cout << "SDL Linked with " << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch);
	AddLog("SDL Linked with " + to_string(linked.major) + '.' + to_string(linked.minor) + '.' + to_string(linked.patch));

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
		//PreGameAppRender();
		gameApp->Render(editorCamera->camera);
		//PostGameAppRender();

		auto item = modules.begin();

		while (item != modules.end() && ret == true) {
			ret = (*item)->PostUpdate();
			++item;
		}

		editorWindow->Render();
	}

	// get game logs
	{
		vector<string> gameLogs = gameApp->GetLogs();

		for (auto it = gameLogs.begin(); it != gameLogs.end(); ++it) {
			AddLog((*it));
		}

		gameApp->ClearLogs();
	}






	const auto frame_end = steady_clock::now();
	const auto frame_duration = frame_end - frame_start;

	if (frame_duration < FDT)
		this_thread::sleep_for(FDT - frame_duration);

	const auto frameEndAfterSleep = steady_clock::now();
	const auto frameDurationAfterSleep = frameEndAfterSleep - frame_start;

	float lastFPS = 1.0f / (frameDurationAfterSleep.count() * 0.000000001f);

	FPS_Log.push_back(lastFPS);
	if (FPS_Log.size() > 100) {
		FPS_Log.erase(FPS_Log.begin());
	}

	return ret;
}

bool EditorApp::Cleanup() {

	editorUI->CleanUp();
	editorInput->CleanUp();
	editorWindow->CleanUp();

	SDL_Quit();

	return true;
}

void EditorApp::WebRequest(const char* url)
{
	ShellExecute(0, 0, url, 0, 0, SW_SHOW);
}

void EditorApp::AddLog(string l)
{
	logs.push_back(l);
}

vector<string> EditorApp::GetLogs()
{
	return logs;
}

void EditorApp::ClearLogs()
{
	logs.clear();
}



//void EditorApp::PreGameAppRender()
//{
//	glGenFramebuffers(1, &gameAppRenderFBO);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, gameAppRenderFBO);
//}
//
//void EditorApp::PostGameAppRender()
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glDeleteFramebuffers(1, &gameAppRenderFBO);
//
//	glGenTextures(1, &gameAppRenderTexture);
//	glBindTexture(GL_TEXTURE_2D, gameAppRenderTexture);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gameAppRenderTexture, 0);
//}
