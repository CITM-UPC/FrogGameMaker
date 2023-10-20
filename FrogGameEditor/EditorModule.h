#pragma once

class EditorApp;

class EditorModule {
public:
	EditorModule(EditorApp* editor) {
		this->editor = editor;
	}

	~EditorModule() {

	}

	virtual bool Start() {
		return true;
	}

	virtual bool PreUpdate() {
		return true;
	}

	virtual bool Update() {
		return true;
	}

	virtual bool PostUpdate() {
		return true;
	}

	virtual bool CleanUp() {
		return true;
	}

	EditorApp* editor = nullptr;

};