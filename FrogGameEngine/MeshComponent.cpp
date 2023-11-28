#include "MeshComponent.h"

MeshComponent::MeshComponent()
{
	componentType = MESH;

}

void MeshComponent::setMesh(Mesh::Ptr mesh)
{
	_mesh = mesh;
}

Mesh::Ptr MeshComponent::getMesh()
{
	return _mesh;
}
