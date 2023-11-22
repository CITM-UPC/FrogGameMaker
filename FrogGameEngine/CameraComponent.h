#pragma once
#include "Component.h"
#include "GameRenderer.h"

class CameraComponent : public Component {
public:

	CameraComponent() {
		componentType = CAMERA;
	}

	void setCamera(Camera camera) {
		_camera = camera;
	}

	Camera getCamera() {
		return _camera;
	}

protected:

private:
	Camera _camera;
};