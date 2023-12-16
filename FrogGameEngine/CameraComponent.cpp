#include "CameraComponent.h"

CameraComponent::CameraComponent(GameObject* owner) : Component(owner)
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

Camera* CameraComponent::getCamera()
{
	return &_camera;
}
