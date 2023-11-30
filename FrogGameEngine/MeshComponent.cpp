#include "MeshComponent.h"

MeshComponent::MeshComponent()
{
	componentType = MESH;

}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::setMesh(Mesh::Ptr mesh)
{
	_mesh = mesh;
}

Mesh::Ptr MeshComponent::getMesh()
{
	return _mesh;
}
