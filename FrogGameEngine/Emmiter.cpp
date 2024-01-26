#include "Emmiter.h"
#include <map>
#include <GL/glew.h>
#include "SpawnModules.h"
#include "BillboardingEM.h"
#include "InitializeModules.h"

Emmiter::Emmiter()
{
	delay = 0;
	maxParticles = 100;
	duration = 10;
	lifetime = 0;
	isLooping = true;
	isON = true;

	spawnModule = std::make_unique<ConstantSpawnRate>(this);

	renderModule = std::make_unique<BillboardRender>(this);

	auto setSpeed = std::make_unique<SetSpeed>();
	setSpeed->speed.usingSingleValue = false;
	setSpeed->speed.rangeValue.lowerLimit = vec3{-0.5, 1, -0.5};
	setSpeed->speed.rangeValue.upperLimit = vec3{ 0.5, 2, 0.5 };


	initializeModules.push_back(std::move(setSpeed));

	RestartParticlePool();
}

Emmiter::~Emmiter()
{
}

void Emmiter::Start()
{
	lifetime = 0;
	while (!usingParticlesIDs.empty()) {
		freeParticlesIDs.push(usingParticlesIDs[usingParticlesIDs.size() - 1]);
		usingParticlesIDs.pop_back();
	}

	if (spawnModule) {
		spawnModule->Reset();
	}

	RestartParticlePool();
}

void Emmiter::Update(double dt)
{
	if (!isON) return;

	lifetime += dt;

	if (lifetime < delay) return;

	if (lifetime < duration + delay || isLooping) {
		if (spawnModule) {
			spawnModule->Update(dt);
		}
	}

	for (auto i = updateModules.begin(); i != updateModules.end(); ++i) {
		for (auto j = usingParticlesIDs.begin(); j != usingParticlesIDs.end(); ++j) {
			(*i)->Update(dt, particles[*j].get());
		}
	}

	std::vector<std::vector<int>::iterator> particlesToFree;

	for (auto i = usingParticlesIDs.begin(); i != usingParticlesIDs.end(); ++i) {
		particles[*i]->Update(dt);
		if (particles[*i]->lifetime > particles[*i]->duration) {
			particlesToFree.push_back(i);
		}
	}

	for (auto i = particlesToFree.rbegin(); i != particlesToFree.rend(); ++i) {
		freeParticlesIDs.push(*(*i));
		usingParticlesIDs.erase(*i);

	}
}

void Emmiter::Render()
{
	//// sort particles by distance to the camera
	//std::map<float, Particle*> particlesToRender;
	//float modelview[16];
	//glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

	//for () {
	//	particlesToRender.insert
	//}

	std::vector<Particle*> particlesToRender;
	for (auto i = usingParticlesIDs.begin(); i != usingParticlesIDs.end(); ++i) {
		particlesToRender.push_back(particles[(*i)].get());
	}

	if (renderModule) {
		for (auto i = particlesToRender.begin(); i != particlesToRender.end(); ++i) {
			renderModule->Update(*i);
		}
	}
}

void Emmiter::SpawnParticles(int amount)
{
	for (int i = 0; i < amount; ++i) {
		if (!freeParticlesIDs.empty()) {
			int spawnedParticleID = freeParticlesIDs.front();
			usingParticlesIDs.push_back(spawnedParticleID);
			freeParticlesIDs.pop();
			InitializeParticle(particles[spawnedParticleID].get());
		}
	}
}

void Emmiter::RestartParticlePool()
{
	usingParticlesIDs.clear();

	while (!freeParticlesIDs.empty()) {
		freeParticlesIDs.pop();
	}

	for (int i = 0; i < maxParticles; ++i) {
		freeParticlesIDs.push(i);
	}

	particles.clear();

	for (int i = 0; i < maxParticles; ++i) {
		particles.push_back(std::move(std::make_unique<Particle>()));
	}

	particles.shrink_to_fit();
}

void Emmiter::InitializeParticle(Particle* particle)
{
	if (spawnModule) {
		particle->duration = spawnModule->duration;
	}

	particle->lifetime = 0;
	particle->position = vec3{ 0, 0, 0 };
	particle->color = vec3{ 0, 0, 0 };

	for (auto i = initializeModules.begin(); i != initializeModules.end(); ++i) {
		(*i)->Initialize(particle);
	}
}

void Emmiter::ClearModules()
{
	spawnModule.reset();
	initializeModules.clear();
	updateModules.clear();
	renderModule.reset();
}

EmmiterSpawnModule* Emmiter::AddModule(EmmiterSpawnModule::EmmiterSpawnModuleType type)
{
	EmmiterSpawnModule* newModule = nullptr;
	switch (type)
	{
	case EmmiterSpawnModule::CONSTANT:
		spawnModule = std::make_unique<ConstantSpawnRate>(this);
		newModule = spawnModule.get();
		break;
	case EmmiterSpawnModule::SINGLE_BURST:
		spawnModule = std::make_unique<SingleBurstSpawn>(this);
		newModule = spawnModule.get();
		break;
	case EmmiterSpawnModule::CONSTANT_BURST:
		spawnModule = std::make_unique<ConstantBurstSpawn>(this);
		newModule = spawnModule.get();
		break;
	default:
		break;
	}
	return newModule;
}

EmmiterInitializeModule* Emmiter::AddModule(EmmiterInitializeModule::EmmiterInitializeModuleType type)
{
	EmmiterInitializeModule* newModule = nullptr;
	switch (type)
	{
	case EmmiterInitializeModule::SET_SPEED:
		initializeModules.push_back(std::move(std::make_unique<SetSpeed>()));
		newModule = initializeModules[initializeModules.size() - 1].get();
		break;
	case EmmiterInitializeModule::SET_COLOR:
		initializeModules.push_back(std::move(std::make_unique<SetColor>()));
		newModule = initializeModules[initializeModules.size() - 1].get();
		break;
	default:
		break;
	}
	return newModule;
}

EmmiterUpdateModule* Emmiter::AddModule(EmmiterUpdateModule::EmmiterUpdateModuleType type)
{
	EmmiterUpdateModule* newModule = nullptr;
	switch (type)
	{
	case EmmiterUpdateModule::CHANGE_COLOR:
		break;
	default:
		break;
	}
	return newModule;
}

EmmiterRenderModule* Emmiter::AddModule(EmmiterRenderModule::EmmiterRenderModuleType type)
{
	EmmiterRenderModule* newModule = nullptr;
	switch (type)
	{
	case EmmiterRenderModule::BILLBOARD:
		renderModule = std::make_unique<BillboardRender>(this);
		newModule = renderModule.get();
		break;
	default:
		break;
	}
	return newModule;
}
