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

	renderModule = std::make_unique<Billboarding>();

	auto setSpeed = std::make_unique<SetSpeed>();
	setSpeed->speed.usingSingleValue = true;
	setSpeed->speed.singleValue = vec3{0, 1, 0};

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

	for (auto i = particles.begin(); i != particles.end(); ++i) {
		(*i)->Update(dt);
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
			usingParticlesIDs.push_back(freeParticlesIDs.front());
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
	particle->lifetime = 0;

	for (auto i = initializeModules.begin(); i != initializeModules.end(); ++i) {
		(*i)->Initialize(particle);
	}
}
