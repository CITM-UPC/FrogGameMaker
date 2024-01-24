#include "Emmiter.h"
#include <map>
#include <GL/glew.h>

Emmiter::Emmiter()
{
}

Emmiter::~Emmiter()
{
}

void Emmiter::Start()
{
	delay = 0;
	while (!usingParticlesIDs.empty()) {
		freeParticlesIDs.push(usingParticlesIDs[usingParticlesIDs.size() - 1]);
		usingParticlesIDs.pop_back();
	}
}

void Emmiter::Update(double dt)
{
	lifetime += dt;

	if (lifetime >= delay) {
		for (auto i = updateModules.begin(); i != updateModules.end(); ++i) {
			(*i).Update(dt, particles);
		}
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

	for (auto i = renderModules.begin(); i != renderModules.end(); ++i) {
		(*i).Update(particles);
	}
}

void Emmiter::SpawnParticles(int amount)
{
	for (int i = 0; i < amount; ++i) {
		if (!freeParticlesIDs.empty()) {
			int spawnedParticleID = freeParticlesIDs.front();
			usingParticlesIDs.push_back(freeParticlesIDs.front());
			freeParticlesIDs.pop();
			InitializeParticle(particles[spawnedParticleID]);
		}
	}
}

void Emmiter::RestartParticlePool()
{

}

void Emmiter::InitializeParticle(Particle& particle)
{
	particle.lifetime = 0;

	for (auto i = initializeModules.begin(); i != initializeModules.end(); ++i) {
		(*i).Initialize(particle);
	}
}
