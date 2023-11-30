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

void EditorObjectSelector::SetGameObjectSelected(GameObject* selected)
{
	gameObjectSelected = selected;
}

GameObject* EditorObjectSelector::GetGameObjectSelected()
{
	return gameObjectSelected;
}
