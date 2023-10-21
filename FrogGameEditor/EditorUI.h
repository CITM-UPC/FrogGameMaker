#pragma once

#include "EditorModule.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "EditorWindow.h"

#include "../FrogGameEngine/GameApp.h"

class EditorUI : public EditorModule
{

public:
	EditorUI(EditorApp* editor) : EditorModule(editor) {


	};

	// TODO: change window and gl_context to pick it from app
	bool Start() {

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();


		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForOpenGL(editor->editorWindow->window, editor->editorWindow->glContext);
		ImGui_ImplOpenGL3_Init();


		// Load Fonts
		// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
		// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
		// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
		// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
		// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
		// - Read 'docs/FONTS.md' for more instructions and details.
		// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
		//io.Fonts->AddFontDefault();
		//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != NULL);

		// Our state
		//bool show_demo_window = true;
		//bool show_another_window = false;
		clear_color = ImVec4(0.039f, 0.039f, 0.039f, 1.00f);

		show_demo_window = true;
		show_another_window = true;
		dockSpaceEnabled = true;
		showHardwareWindow = true;
		showAboutPopup = false;

		return true;
	}

	bool PreUpdate() {
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		/*SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
		}*/

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		if (dockSpaceEnabled) {
			ImGuiDockNodeFlags dock_flags = 0;
			dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
			ImGui::DockSpaceOverViewport(0, dock_flags);
		}

		return true;
	}

	bool Update() {

		// main menu bar
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Info")) {

				if (ImGui::MenuItem("Hardware Information")) {
					showHardwareWindow = !showHardwareWindow;
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help")) {

				if (ImGui::MenuItem("Demo Window")) {
					show_demo_window = !show_demo_window;
				}

				if (ImGui::MenuItem("About")) {
					showAboutPopup = !showAboutPopup;
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
		
		// about poput (there is a bug in imgui that causes that you cannot open a popup directly from the menu, this is a kinda solution)
		{
			if (showAboutPopup) {
				ImGui::OpenPopup("About");
				showAboutPopup = false;
			}

			ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			if (ImGui::BeginPopupModal("About")) {
				{
					// name engine + version
					ImGui::SeparatorText("Frog Game Engine v0.1");

					// made by
					ImGui::Text("Made by: ");
					ImGui::Text("   Victor Martin (Github: VicMarBall)");
					ImGui::Text("   Ari Sevcik (Github: AriSevcik)");

					// external libraries
					{
						ImGui::SeparatorText("External Libraries Used: ");
						// sdl
						{
							SDL_version sdlVersion;
							SDL_GetVersion(&sdlVersion);

							ImGui::Bullet(); ImGui::Text("SDL %d.%d.%d", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
						}
						
						// opengl
						{
							ImGui::Bullet(); ImGui::Text("OpenGL %s", glGetString(GL_VERSION));
						}

						// glew
						{
							ImGui::Bullet(); ImGui::Text("GLEW %s", glewGetString(GLEW_VERSION));
						}

						// imgui
						{
							ImGui::Bullet(); ImGui::Text("ImGui %s", IMGUI_VERSION);
						}

						// glu
						{
							ImGui::Bullet(); ImGui::Text("GLU --TODO--");
						}

						// devil
						{
							ImGui::Bullet(); ImGui::Text("DevIL --TODO--");
						}

						// assimp
						{
							ImGui::Bullet(); ImGui::Text("Assimp --TODO--");
						}
						
					}

					{
						ImGui::SeparatorText("License");

						// --TODO-- read directly the license document (?)
						ImGui::Text("MIT License");
						ImGui::Text("");
						ImGui::Text("Copyright(c) 2023 CITM - UPC");
						ImGui::Text("");
						ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
						ImGui::Text("of this software and associated documentation files(the \"Software\"), to deal");
						ImGui::Text("in the Software without restriction, including without limitation the rights");
						ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
						ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
						ImGui::Text("furnished to do so, subject to the following conditions :");
						ImGui::Text("");
						ImGui::Text("The above copyright notice and this permission notice shall be included in all");
						ImGui::Text("copies or substantial portions of the Software.");
						ImGui::Text("");
						ImGui::Text("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
						ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
						ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
						ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
						ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
						ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
						ImGui::Text("SOFTWARE.");
					}

					ImGui::Separator();

					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}

		}
		

		// windows
		if (showHardwareWindow) {
			ImGui::Begin("Hardware");

			const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
			const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model			

			ImGui::Text("%s", vendor);
			ImGui::Text("%s", renderer);

			SDL_version sdlVersion;
			SDL_GetVersion(&sdlVersion);

			ImGui::Text("SDL Version: %d.%d.%d", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);

			for (int i = 0; i < SDL_GetNumVideoDrivers(); ++i) {
				ImGui::Text("%s", SDL_GetVideoDriver(i));
			}
			

			ImGui::Text("CPU's Cores:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d (Cache: %d kb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());

			ImGui::End();
		}

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window) {
			ImGui::ShowDemoWindow(&show_demo_window);
			ImGui::IsWindowDocked();
		}

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);
			ImGui::Checkbox("Docking", &dockSpaceEnabled);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;

		}

		return true;
	}

	bool PostUpdate() {
		ImGui::Render();
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//SDL_GL_SwapWindow(window);
		return true;
	}

	bool CleanUp() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		return true;
	}


	bool show_demo_window;
	bool show_another_window;
	bool dockSpaceEnabled;
	bool showHardwareWindow;
	bool showAboutPopup;

	ImVec4 clear_color;
};