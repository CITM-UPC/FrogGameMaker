#pragma once
// holds the information on how the particles behave
// only one behavior
// loopable?
// duration?
// delay? (to put an emmiter after another)
// uses the transform of the game object the particle system component belongs
// ranges of values if random (template of ranges for random?)
// 
// maybe create a "component type" for specific behaviors and having them in a vector
// particle module in the powerpoints
// 
// list/vector of the particles

#include <vector>
#include <queue>
#include <array>
#include "Particle.h"
#include <memory>

#include "EmmiterModule.h"

class Emmiter {
public:
	Emmiter();
	~Emmiter();

	void Start();
	void Update(double dt);
	void Render();

	void SpawnParticles(int amount);
	
	// function for when we change the maxParticles or when we start
	void RestartParticlePool();

	void InitializeParticle(Particle* particle);

	void ClearModules();

	EmmiterSpawnModule* AddModule(EmmiterSpawnModule::EmmiterSpawnModuleType type);
	EmmiterInitializeModule* AddModule(EmmiterInitializeModule::EmmiterInitializeModuleType type);
	EmmiterUpdateModule* AddModule(EmmiterUpdateModule::EmmiterUpdateModuleType type);
	EmmiterRenderModule* AddModule(EmmiterRenderModule::EmmiterRenderModuleType type);


public:
	bool isON;

	int maxParticles;

	float duration;
	float lifetime;

	float delay;

	bool isLooping;

	// specific behaviors
	std::unique_ptr<EmmiterSpawnModule> spawnModule;

	std::vector<std::unique_ptr<EmmiterInitializeModule>> initializeModules;

	std::vector<std::unique_ptr<EmmiterUpdateModule>> updateModules;

	std::unique_ptr<EmmiterRenderModule> renderModule;	

private: 
	std::vector<std::unique_ptr<Particle>> particles;
	std::vector<int> usingParticlesIDs;
	std::queue<int> freeParticlesIDs;

};