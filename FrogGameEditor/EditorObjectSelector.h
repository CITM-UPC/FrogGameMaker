#pragma once
#include "EditorModule.h"

class EditorObjectSelector : public EditorModule {
public:
	EditorObjectSelector();

	bool Start();
	bool Update();
	bool PostUpdate();

	void SetGameObjectSelected(GameObject* selected);
	GameObject* GetGameObjectSelected();

	GameObject* gameObjectSelected = nullptr;
};