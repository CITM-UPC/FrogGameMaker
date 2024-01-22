#include "Emmiter.h"

Emmiter::Emmiter()
{
}

Emmiter::~Emmiter()
{
}

void Emmiter::PlayParticles()
{
}

void Emmiter::UpdateParticles(float dt)
{
	for (auto i = updateModules.begin(); i != updateModules.end(); ++i) {
		(*i).Update(dt, particles);
	}
}

void Emmiter::RenderParticles()
{
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
	for (auto i = initializeModules.begin(); i != initializeModules.end(); ++i) {
		(*i).Initialize(particle);
	}
}
