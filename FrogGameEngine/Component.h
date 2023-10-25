#pragma once

#include "Types.h"

#include <glm/ext/matrix_transform.hpp>

class Component {
	void Start();
	void Update();

};


class Transform : public Component {
public:

	inline vec3 getPosition() { 
		return _transform[3];
	}

	// not in the mood to do rotations --TODO--
	inline vec3 getRotation() {
		return _transform[3];
	}
	
	inline vec3 getScale() { 
		double x = _transform[0].length();
		double y = _transform[1].length();
		double z = _transform[2].length();

		vec3 scale = vec3(x, y, z);

		return scale;
	}


private:
	mat4 _transform;

};