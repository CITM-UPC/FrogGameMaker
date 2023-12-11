#pragma once
#include <chrono>
#include <string>

#include "Types.h"
#include "GameRenderer.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

#include "Scene.h"

class GameApp
{
public:
	GameApp();
	~GameApp();

	//enum class RenderModes { RELEASE, DEBUG };

	Camera* actualCamera;

	void EditorStart();
	void EditorStep(std::chrono::duration<double> dt);
	void GameStart();
	void GameStep(std::chrono::duration<double> dt);
	void EditorRender(Camera camera);
	void GameRender(Camera camera);
	void CleanUp();

	vec3 positionCube = { 0, 0, 0 }, rotationCube = { 0, 0, 0 }, scaleCube = { 1, 1, 1 };


	Scene* scene = nullptr;
	
	GameObject* house = nullptr;

	void AddLog(string l);

	vector<string> GetLogs();

	void ClearLogs();

private:
	vector<string> logs;

};

