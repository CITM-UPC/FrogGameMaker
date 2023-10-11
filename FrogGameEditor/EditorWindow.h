#pragma once

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

private:

};

EditorWindow::EditorWindow()
{
}

EditorWindow::~EditorWindow()
{
}

bool EditorWindow::Start() {

	return true;
}

bool EditorWindow::PreUpdate() {

	return true;
}

bool EditorWindow::Update() {

	return true;
}

bool EditorWindow::PostUpdate() {

	return true;
}

bool EditorWindow::CleanUp() {

	return true;
}