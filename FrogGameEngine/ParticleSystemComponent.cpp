#include "ParticleSystemComponent.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* owner) : Component(owner)
{
	componentType = PARTICLE_SYSTEM;
}

ParticleSystemComponent::~ParticleSystemComponent()
{
}

void ParticleSystemComponent::Update(double dt)
{
	if (isON) {
		for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
			(*i).Update(dt);
		}
	}
}

void ParticleSystemComponent::Render()
{
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i).Render();
	}
}

void ParticleSystemComponent::Play()
{
	isON = true;
}

void ParticleSystemComponent::Stop()
{
	isON = false;
}

void ParticleSystemComponent::Restart()
{
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i).Start();
	}
}
