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
	Play();
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i)->Start();
	}
}

void ParticleSystemComponent::ClearEmmiters()
{
	emmiters.clear();
}

Emmiter* ParticleSystemComponent::AddEmmiter()
{
	emmiters.push_back(std::move(std::make_unique<Emmiter>()));
	return emmiters[emmiters.size() - 1].get();
}

bool ParticleSystemComponent::IsON()
{
	return isON;
}
