#pragma once

#include <vector>
#include <ostream>
#include <istream>

struct MeshLoader
{
	struct VertexV3T2 {
		struct { float x, y, z; } vertex;
		struct { float s, t; } texCoords;
	};

	std::vector<VertexV3T2> vertex_data;
	std::vector<unsigned int> index_data;

	std::ostream& serialize(std::ostream& os) const;
	std::istream& deserialize(std::istream& is);

};

inline std::ostream& operator<<(std::ostream& os, const MeshLoader& mesh) {
	return mesh.serialize(os);
}

inline std::istream& operator>>(std::istream& is, MeshLoader& mesh) {
	return mesh.deserialize(is);
}