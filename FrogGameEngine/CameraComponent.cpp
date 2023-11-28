#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	componentType = CAMERA;
	
}

void CameraComponent::setCamera(Camera camera)
{
	_camera = camera;
}

Camera CameraComponent::getCamera()
{
	return _camera;
}
