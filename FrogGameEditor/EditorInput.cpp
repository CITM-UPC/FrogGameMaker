#include "EditorApp.h"

#include "EditorInput.h"

EditorInput::EditorInput() : EditorModule()
{
}

EditorInput::~EditorInput()
{
}

bool EditorInput::Start() {

	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouseButtons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);

	return true;
}

bool EditorInput::PreUpdate() {

	string dropped_filedir;

	SDL_Event event;

	windowSizeHasUpdated = false;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouseButtons[i] == KEY_DOWN)
			mouseButtons[i] = KEY_REPEAT;

		if (mouseButtons[i] == KEY_UP)
			mouseButtons[i] = KEY_IDLE;
	}

	mouseMotionX = 0;
	mouseMotionY = 0;

	mouseWheelScroll = 0;

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
		case SDL_MOUSEBUTTONDOWN:
			mouseButtons[event.button.button - 1] = KEY_DOWN;
			//LOG("Mouse button %d down", event.button.button-1);
			break;

		case SDL_MOUSEBUTTONUP:
			mouseButtons[event.button.button - 1] = KEY_UP;
			//LOG("Mouse button %d up", event.button.button-1);
			break;
		case (SDL_DROPFILE): {      // In case if dropped file
			dropped_filedir = event.drop.file;

			if (dropped_filedir.ends_with(".fbx")) {
				/*if (!dropped_filedir.starts_with("Assets/"))
					filesystem::copy(dropped_filedir, "Assets");*/

				GameObject* newMesh = editor->gameApp->scene->AddGameObject();
				auto mesh_ptrs = Mesh::loadFromFile(dropped_filedir);
				editor->AddLog("Mesh loaded from " + dropped_filedir);
				newMesh->AddMeshWithTexture(mesh_ptrs);

			}
			else if (dropped_filedir.ends_with(".png") || dropped_filedir.ends_with(".dds")) {
				/*if (!dropped_filedir.starts_with("Assets/"))
					filesystem::copy(dropped_filedir, "Assets");*/
				if (editor->editorUI->gameObjectSelected != nullptr) {
					TextureComponent* textureComponent = (TextureComponent*)editor->editorUI->gameObjectSelected->GetComponent(TEXTURE);
					MeshComponent* meshComponent = (MeshComponent*)editor->editorUI->gameObjectSelected->GetComponent(MESH);
					if (meshComponent->getMesh() != nullptr) {
						meshComponent->getMesh()->loadTextureToMesh(dropped_filedir);
						textureComponent->setTexture(meshComponent->getMesh()->texture);
						editor->AddLog("Texture " + dropped_filedir + " applied to " + editor->editorUI->gameObjectSelected->name);
					}

				}

			}
			else {

			}

			// Shows directory of dropped file
			/*SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_INFORMATION,
				"File dropped on window",
				dropped_filedir,
				editor->editorWindow->window
			);
			SDL_free(dropped_filedir);*/ }   // Free dropped_filedir memory
						   break;
		case SDL_MOUSEMOTION:
			mouseMotionX = event.motion.xrel;
			mouseMotionY = event.motion.yrel;
			break;
		case SDL_MOUSEWHEEL:
			mouseWheelScroll = event.wheel.y;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				windowSizeHasUpdated = true;
				editor->editorWindow->UpdateSizes(event.window.data1, event.window.data2);
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
	delete[] keyboard;

	return true;
}