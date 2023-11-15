#pragma once
#include "Component.h"

class MeshComponent : public Component {
public:

	MeshComponent() {
		componentType = MESH;
	}

	void setMesh(Mesh::Ptr mesh) {
		_mesh = mesh;
	}

	Mesh::Ptr getMesh() {
		return _mesh;
	}

protected:

private:
	Mesh::Ptr _mesh = nullptr;
};