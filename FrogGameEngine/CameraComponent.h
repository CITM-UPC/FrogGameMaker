#pragma once
#include "Component.h"
#include "GameRenderer.h"
#include "TransformComponent.h"

class CameraComponent : public Component {
public:

	CameraComponent(GameObject* owner);
	~CameraComponent();

	void setCamera(Camera camera);
	Camera* getCamera();

	TransformComponent* getTransform();

	void Render(vec3 cameraPosition);

protected:

private:
	TransformComponent* transform;

	Camera _camera;
};