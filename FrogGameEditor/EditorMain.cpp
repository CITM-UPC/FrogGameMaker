#include <iostream>
#include "EditorApp.h"

int main() {

	EditorApp* editorApp = new EditorApp;

	// start
	bool toContinue = true;
	toContinue = editorApp->Start();
	if (toContinue) {

		while (toContinue) {
			toContinue = editorApp->Update();
		}

		editorApp->Cleanup();

		return 1;
	}
	else {
		std::cout << "ERROR" << std::endl;
		return -1;
	}

	return 0;
}