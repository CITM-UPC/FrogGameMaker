#pragma once
#include <chrono>
#include <string>
#include <filesystem>
#include <list>

#include "Types.h"
#include "GameRenderer.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

#include "Scene.h"

struct Paths {

	std::string name;
	filesystem::path assetsPath;
	std::vector<filesystem::path> libraryPath;

};

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
	void Render(Camera camera);
	void CleanUp();

	vec3 positionCube = { 0, 0, 0 }, rotationCube = { 0, 0, 0 }, scaleCube = { 1, 1, 1 };


	Scene* scene = nullptr;
	
	GameObject* house = nullptr;

	vector<Paths> allAssets;

	void AddLog(string l);

	vector<string> GetLogs();

	void ClearLogs();

private:
	vector<string> logs;

};



