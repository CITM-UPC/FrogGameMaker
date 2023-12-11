#pragma once
#include "EditorModule.h"

class EditorObjectSelector : public EditorModule {
public:
	EditorObjectSelector();

	bool Start();
	bool Update();
	bool PostUpdate();

	void SearchObject(int x, int y);
	void CheckRayHitParent(int x, int y, GameObject* parent, vector<GameObject*> hitted, vector<float> distances);
	bool RayHitsAABB(int x, int y, AABBox aabb);
	bool RayHitsGameObject(int x, int y, GameObject go, float& distance);

	void SetGameObjectSelected(GameObject* selected);
	GameObject* GetGameObjectSelected();

	GameObject* gameObjectSelected = nullptr;
};