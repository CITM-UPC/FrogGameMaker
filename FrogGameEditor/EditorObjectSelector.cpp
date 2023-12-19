#include "EditorApp.h"

#include <GL/glew.h>

#include "EditorObjectSelector.h"

EditorObjectSelector::EditorObjectSelector()
{
}

bool EditorObjectSelector::Start()
{
	return true;
}

bool EditorObjectSelector::Update()
{
	if (gameObjectSelected == nullptr) {
		return true;
	}
	glColor3ub(255, 0, 0);
	glPointSize(12);

	TransformComponent* transform = gameObjectSelected->GetComponent<TransformComponent>();
	glBegin(GL_POINTS);
	glVertex3f(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
	glEnd();

	return true;
}

bool EditorObjectSelector::PostUpdate()
{


	return true;
}

void EditorObjectSelector::SearchObject(int x, int y)
{
	vector<GameObject*> hitted;
	vector<float> distances;

	if (!RayHitsAABB(x, y, editor->gameApp->scene->aabb)) {
		return;
	}

	for (auto i = editor->gameApp->scene->children.begin(); i != editor->gameApp->scene->children.end(); ++i) {
		if (RayHitsAABB(x, y, (*i)->GetBoundingBox())) {
			CheckRayHitParent(x, y, (*i).get(), hitted, distances);
		}
	}

	if (distances.empty()) {
		return;
	}

	float smallestDistance = distances[0];
	float smallestDistanceIndex = 0;
	for (auto i = 0; i < distances.size(); ++i) {
		if (distances[i] < smallestDistance) {
			smallestDistance = distances[i];
			smallestDistanceIndex = i;
		}
	}

	gameObjectSelected = hitted[smallestDistanceIndex];

}

void EditorObjectSelector::CheckRayHitParent(int x, int y, GameObject* parent, vector<GameObject*> hitted, vector<float> distances)
{
	float distance;
	if (RayHitsGameObject(x, y, parent, distance)) {
		hitted.push_back(parent);
		distances.push_back(distance);

		if (parent->children.empty()) {
			return;
		}

		for (auto i = parent->children.begin(); i != parent->children.end(); ++i) {
			if (RayHitsAABB(x, y, (*i)->GetBoundingBox())) {
				CheckRayHitParent(x, y, (*i).get(), hitted, distances);
			}
		}
	}
}

bool EditorObjectSelector::RayHitsAABB(int x, int y, AABBox aabb)
{
	return false;
}

bool EditorObjectSelector::RayHitsGameObject(int x, int y, GameObject* go, float& distance)
{
	if (go->GetComponent<MeshComponent>() == nullptr) {
		return false;
	}

	// if (ray hits mesh)
	// save distance
	// return true;

	return false;
}

void EditorObjectSelector::SetGameObjectSelected(GameObject* selected)
{
	gameObjectSelected = selected;
}

GameObject* EditorObjectSelector::GetGameObjectSelected()
{
	return gameObjectSelected;
}
