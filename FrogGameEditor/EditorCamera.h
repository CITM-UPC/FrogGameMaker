#pragma once
#include "EditorModule.h"
#include "EditorUI.h"

#include "../FrogGameEngine/GameRenderer.h"

class EditorCamera : public EditorModule {
public:
	EditorCamera(EditorApp* editor) : EditorModule(editor) {

	};

	bool Update() {

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

		//else if

		//// While Right clicking, “WASD” fps-like movement and free look around must be enabled
		//if (/*right click*/) {
		//	if (/*W*/) {
		//		// move eye (position) and center (looking point) at local directions
		//	}
		//	if (/*A*/) {
		//		// move eye (position) and center (looking point) at local directions
		//	}
		//	if (/*S*/) {
		//		// move eye (position) and center (looking point) at local directions
		//	}
		//	if (/*D*/) {
		//		// move eye (position) and center (looking point) at local directions
		//	}
		//}

		// else

		//// Mouse wheel should zoom in and out
		//if (/*mouse wheel*/) {
		//	// move eye (position) locally on z, but do not cross center (looking point)
		//}

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

		if (editor->editorInput->GetKey(SDL_SCANCODE_W)) {
			TranslateLocally(vec3(0, 0, -speed));
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_S)) {
			TranslateLocally(vec3(0, 0, speed));
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_A)) {
			TranslateLocally(vec3(-speed, 0, 0));
		}

		if (editor->editorInput->GetKey(SDL_SCANCODE_D)) {
			TranslateLocally(vec3(speed, 0, 0));
		}

		return true;
	}

	void TranslateLocally(vec3 translation) {
		vec3 localZ = glm::normalize(camera.eye - camera.center);
		vec3 localY = glm::normalize(camera.up);
		vec3 localX = glm::normalize(glm::cross(localY, localZ));

		vec3 localTranslation = glm::dmat3(localX, localY, localZ) * translation;

		camera.center += localTranslation;
		camera.eye += localTranslation;
	}

	void OrbitAround(vec2 mouseMovement) {
		// move only eye (position) locally on x and y

		//double distanceZ = glm::distance(camera.eye, camera.center);

		/*mat4 transformMatrix = camera.computeLookAt();
		mat4 rotatedMatrix = glm::rotate(transformMatrix, 1.0, vec3(mouseMovement.y, mouseMovement.x, 0));

		camera.eye = vec3(glm::length(rotatedMatrix[0]), glm::length(rotatedMatrix[1]), glm::length(rotatedMatrix[2]));*/

		/*vec3 translation = vec3(-mouseMovement.x, mouseMovement.y, 0);

		vec3 localZ = glm::normalize(camera.eye - camera.center);
		vec3 localY = glm::normalize(camera.up);
		vec3 localX = glm::normalize(glm::cross(localY, localZ));

		vec3 localTranslation = glm::dmat3(localX, localY, localZ) * translation;

		camera.eye += localTranslation;

		camera.eye = camera.center + ((glm::normalize(localZ)) * distanceZ);*/

		//camera.computeLookAt();
	}

	void FocusOn(vec3 focusPoint) {
		// move center (looking point) to the selected game object position
		// then move eye (position) to a distance on the line vector z crossing center (looking point)
		// --TODO-- (?) is there a way to get how big the 3d model is? to put the vision around the whole mesh and not only from one point
		vec3 localZ = camera.eye - camera.center;
		camera.center = focusPoint;
		camera.eye = camera.center + ((glm::normalize(localZ)) * 10.0 /*distance*/);
	}

	float baseSpeed = 0.5;

	Camera camera;
};