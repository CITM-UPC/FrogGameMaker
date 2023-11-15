#include "EditorApp.h"

#include "EditorInput.h"

#include "EditorCamera.h"

#include "../FrogGameEngine/TransformComponent.h"

EditorCamera::EditorCamera() : EditorModule() { }

bool EditorCamera::Start() {

	camera.aspect = (double)editor->editorWindow->width / (double)editor->editorWindow->height;

	return true;
}

bool EditorCamera::Update() {

	if (editor->editorInput->WindowSizeHasUpdated()) {
		camera.aspect = (double)editor->editorWindow->width / (double)editor->editorWindow->height;
	}

	// Holding SHIFT duplicates movement speed
	float speed = baseSpeed;
	if (editor->editorInput->GetKey(SDL_SCANCODE_LSHIFT)) {
		speed = speed * 2.0 /*multiplying factor*/;
	}

	// Alt+Left click should orbit the object
	if (editor->editorInput->GetKey(SDL_SCANCODE_LALT)) {
		if (editor->editorInput->GetMouseButtonDown(SDL_BUTTON_LEFT)) {
			OrbitAround(editor->editorInput->GetMouseMotion());
		}
	}

	// While Right clicking, “WASD” fps-like movement and free look around must be enabled
	else if (editor->editorInput->GetMouseButtonDown(SDL_BUTTON_RIGHT)) {
		if (editor->editorInput->GetKey(SDL_SCANCODE_W)) {
			TranslateLocally(vec3(0, 0, -speed));
		}
		if (editor->editorInput->GetKey(SDL_SCANCODE_A)) {
			TranslateLocally(vec3(-speed, 0, 0));
		}
		if (editor->editorInput->GetKey(SDL_SCANCODE_S)) {
			TranslateLocally(vec3(0, 0, speed));
		}
		if (editor->editorInput->GetKey(SDL_SCANCODE_D)) {
			TranslateLocally(vec3(speed, 0, 0));
		}

		LookAround(editor->editorInput->GetMouseMotion());
	}

	// Mouse wheel should zoom in and out
	if (editor->editorInput->GetMouseWheelScroll() != 0) {
		CameraZoom(-editor->editorInput->GetMouseWheelScroll());
	}

	// Pressing “f” should focus the camera around the geometry
	if (editor->editorInput->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		if (editor->editorUI->gameObjectSelected != nullptr) {
			if (editor->editorUI->gameObjectSelected->GetComponent(TRANSFORM) != nullptr) {
				TransformComponent* gameObjectTransform = (TransformComponent*)editor->editorUI->gameObjectSelected->GetComponent(TRANSFORM);
				vec3 focusPoint = gameObjectTransform->getPosition();
				FocusOn(focusPoint);
			}
		}
	}

	return true;
}

void EditorCamera::TranslateLocally(vec3 translation) {

	vec3 localZ = glm::normalize(camera.eye - camera.center);
	vec3 localY = glm::normalize(camera.up);
	vec3 localX = glm::normalize(glm::cross(localY, localZ));

	vec3 localTranslation = glm::dmat3(localX, localY, localZ) * translation;

	camera.center += localTranslation;
	camera.eye += localTranslation;
}

void EditorCamera::OrbitAround(vec2 motion) {

	double sensibility = 0.1;

	if (motion.x != 0) {
		vec3 localZ = camera.eye - camera.center;
		vec3 newLocalZ = glm::rotate(localZ, glm::radians((-motion.x) * sensibility), vec3(0, 1.0f, 0));

		if (!(glm::normalize(newLocalZ).y >= 0.99 || glm::normalize(newLocalZ).y <= -0.99)) {
			camera.eye = camera.center + newLocalZ;
		}
	}

	if (motion.y != 0) {
		vec3 localX;
		localX.x = camera.computeLookAt()[0].x;
		localX.y = camera.computeLookAt()[1].x;
		localX.z = camera.computeLookAt()[2].x;

		vec3 localZ = camera.eye - camera.center;
		vec3 newLocalZ = glm::rotate(localZ, glm::radians((-motion.y) * sensibility), localX);

		if (!(glm::normalize(newLocalZ).y >= 0.99 || glm::normalize(newLocalZ).y <= -0.99)) {

			camera.eye = camera.center + newLocalZ;
		}
	}
}

void EditorCamera::LookAround(vec2 motion) {

	double sensibility = 0.1;

	if (motion.x != 0) {
		vec3 localZ = camera.eye - camera.center;
		vec3 newLocalZ = glm::rotate(localZ, glm::radians((-motion.x) * sensibility), vec3(0, 1.0f, 0));
		if (!(glm::normalize(newLocalZ).y >= 0.99 || glm::normalize(newLocalZ).y <= -0.99)) {

			camera.center = camera.eye - newLocalZ;
		}
	}

	if (motion.y != 0) {
		vec3 localX;
		localX.x = camera.computeLookAt()[0].x;
		localX.y = camera.computeLookAt()[1].x;
		localX.z = camera.computeLookAt()[2].x;


		vec3 localZ = camera.eye - camera.center;
		vec3 newLocalZ = glm::rotate(localZ, glm::radians((-motion.y) * sensibility), localX);

		if (!(glm::normalize(newLocalZ).y >= 0.99 || glm::normalize(newLocalZ).y < -0.99)) {

			camera.center = camera.eye - newLocalZ;
		}
	}
}

void EditorCamera::CameraZoom(double amount) {

	double distanceToCenter = glm::distance(camera.eye, camera.center);
	vec3 localZ = glm::normalize(camera.eye - camera.center);

	camera.eye += localZ * amount * (distanceToCenter * 0.1f);
}

void EditorCamera::FocusOn(vec3 focusPoint) {

	// move center (looking point) to the selected game object position
	// then move eye (position) to a distance on the line vector z crossing center (looking point)
	// --TODO-- (?) is there a way to get how big the 3d model is? to put the vision around the whole mesh and not only from one point
	vec3 localZ = camera.eye - camera.center;
	camera.center = focusPoint;
	camera.eye = camera.center + ((glm::normalize(localZ)) * 10.0 /*distance*/);
}
