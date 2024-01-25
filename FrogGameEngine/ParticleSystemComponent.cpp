#include "ParticleSystemComponent.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* owner) : Component(owner)
{
	componentType = PARTICLE_SYSTEM;
	isON = true;
	AddEmmiter();
}

ParticleSystemComponent::~ParticleSystemComponent()
{
}

void ParticleSystemComponent::Update(double dt)
{
	if (isON) {
		for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
			(*i)->Update(dt);
		}
	}
}

void ParticleSystemComponent::Render()
{
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i)->Render();
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

void ParticleSystemComponent::Replay()
{
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i)->Start();
	}
}

void ParticleSystemComponent::AddEmmiter()
{
	emmiters.push_back(std::move(std::make_unique<Emmiter>()));
}

bool ParticleSystemComponent::IsON()
{
	return isON;
}
