#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	componentType = CAMERA;
	
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::setCamera(Camera camera)
{
	_camera = camera;
}

Camera CameraComponent::getCamera()
{
	return _camera;
}
