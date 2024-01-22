#include "ParticleSystemComponent.h"

void ParticleSystemComponent::Update(float dt)
{
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i).Update(dt);
	}
}

void ParticleSystemComponent::Render()
{
	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		(*i).Render();

	}
}
