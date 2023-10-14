#pragma once
#include <chrono>

#include "Types.h"
#include "GameRenderer.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

class GameApp
{
public:
	GameApp();
	~GameApp();

	enum class RenderModes { RELEASE, DEBUG };

	Camera camera;

	void Step(std::chrono::duration<double> dt);
	void Render(RenderModes renderMode);

	vec3 positionCube = { 0, 0, 0 }, rotationCube = { 0, 0, 0 }, scaleCube = { 1, 1, 1 };

private:

};

