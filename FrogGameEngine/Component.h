#pragma once

#include "Types.h"
#include "Mesh.h"
#include "Texture2D.h"
#include <glm/ext/matrix_transform.hpp>
#include <list>

enum ComponentType {
	NONE = 0,
	TRANSFORM,
	MESH,
	TEXTURE

};

class Component {
public:
	virtual void Start() {};
	virtual void Update() {};

	ComponentType componentType = NONE;
};



class TransformComponent : public Component {
public:

	TransformComponent() {
		_transform = mat4(1.0f);
		componentType = TRANSFORM;
	}

	inline vec3 getPosition() { 
		vec3 ret;
		ret.x = _transform[0][3];
		ret.y = _transform[1][3];
		ret.z = _transform[2][3];

		return ret;
	}

	double toleranceCheckFix(double n, int c = 0) {
		if (abs(n - c) < 1e-5) {
			n = c;
		}

		return n;
	}

	// not in the mood to do rotations --TODO--
	inline vec3 getRotation() {

		vec3 inverseScaleVec;
		inverseScaleVec.x = 1.0 / getScale().x;
		inverseScaleVec.y = 1.0 / getScale().y;
		inverseScaleVec.z = 1.0 / getScale().z;


		glm::dmat3 rotationMatrix;
		rotationMatrix[0][0] = _transform[0][0] * inverseScaleVec.x;
		rotationMatrix[0][1] = _transform[0][1] * inverseScaleVec.x;
		rotationMatrix[0][2] = _transform[0][2] * inverseScaleVec.x;

		rotationMatrix[1][0] = _transform[1][0] * inverseScaleVec.y;
		rotationMatrix[1][1] = _transform[1][1] * inverseScaleVec.y;
		rotationMatrix[1][2] = _transform[1][2] * inverseScaleVec.y;

		rotationMatrix[2][0] = _transform[2][0] * inverseScaleVec.z;
		rotationMatrix[2][1] = _transform[2][1] * inverseScaleVec.z;
		rotationMatrix[2][2] = _transform[2][2] * inverseScaleVec.z;


		float rX;
		float rY;
		float rZ;

		vec3 rotEulerAngles;
		rotEulerAngles.y = -glm::asin(rotationMatrix[2][0]);

		rotEulerAngles.x = glm::acos(rotationMatrix[0][0]);
		rotEulerAngles.z = glm::asin(rotationMatrix[2][0]);




		if (toleranceCheckFix(-rotationMatrix[2][0] - 1) + 1 == 1) {
			rotEulerAngles.y = 90;
			rotEulerAngles.x = atan2(rotationMatrix[1][2], rotationMatrix[1][1]);
			rotEulerAngles.z = 0;
		}
		else if (toleranceCheckFix(-rotationMatrix[2][0] + 1) - 1 == -1) {
			rotEulerAngles.y = 3 * 90;
			rotEulerAngles.x = atan2(rotationMatrix[1][2], rotationMatrix[1][1]);
			rotEulerAngles.z = 0;
		}
		else {
			rotEulerAngles.y = asin(-rotationMatrix[2][0]);
			rotEulerAngles.z = atan2(rotationMatrix[2][1], rotationMatrix[2][2]);
			rotEulerAngles.x = atan2(rotationMatrix[1][0], rotationMatrix[0][0]);
		}


		



		return rotEulerAngles;
	}
	
	inline vec3 getScale() { 

		vec3 xCol;
		xCol.x = _transform[0][0];
		xCol.y = _transform[1][0];
		xCol.z = _transform[2][0];

		vec3 yCol;
		yCol.x = _transform[0][1];
		yCol.y = _transform[1][1];
		yCol.z = _transform[2][1];

		vec3 zCol;
		zCol.x = _transform[0][2];
		zCol.y = _transform[1][2];
		zCol.z = _transform[2][2];

		double x = glm::length(xCol);
		double y = glm::length(yCol);
		double z = glm::length(zCol);

		vec3 scale = vec3(x, y, z);

		return scale;
	}

protected:

private:
	mat4 _transform;

};

class MeshComponent : public Component {
public:

	MeshComponent() {
		componentType = MESH;
	}

	void setMesh(Mesh* mesh) {
		_mesh = mesh;
	}

protected:

private:
	Mesh* _mesh = nullptr;
};

class TextureComponent : public Component {
public:

	TextureComponent() {
		componentType = TEXTURE;
	}

	void setTexture(Texture2D* texture) {
		_texture = texture;
	}

	Texture2D* getTexture() {
		return _texture;
	}

protected:

private:
	Texture2D* _texture;
};