#pragma once
#include "Component.h"
#include "GameRenderer.h"

class CameraComponent : public Component {
public:

	CameraComponent();

	void setCamera(Camera camera);
	Camera getCamera();

protected:

private:
	Camera _camera;
};