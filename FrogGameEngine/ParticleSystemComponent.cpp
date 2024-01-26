#include "ParticleSystemComponent.h"
#include "GameObject.h"
#include "SingleOrRandom.h"
#include <ostream>
#include <istream>
#include <fstream>

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

void ParticleSystemComponent::Save()
{
	std::string fileName = "Library/Particles/" + owner->name + ".particle";
	std::ofstream oFile(fileName, std::ios::binary);

	size_t vLength = emmiters.size();
	oFile.write((char*)&vLength, sizeof(vLength));

	for (auto i = emmiters.begin(); i != emmiters.end(); ++i) {
		bool moduleExistence;

		if ((*i)->spawnModule) {
			moduleExistence = true;
			oFile.write((char*)&moduleExistence, sizeof(moduleExistence));

			oFile.write((char*)&(*i)->spawnModule->type, sizeof((*i)->spawnModule->type));

			float spawnRate;
			float amount;
			switch ((*i)->spawnModule->type)
			{
			case EmmiterSpawnModule::EmmiterSpawnModuleType::CONSTANT:
				spawnRate = (*i)->spawnModule->getSpawnRate();
				oFile.write((char*)&spawnRate, sizeof(spawnRate));
				break;
			case EmmiterSpawnModule::EmmiterSpawnModuleType::SINGLE_BURST:
				amount = (*i)->spawnModule->getAmount();
				oFile.write((char*)&amount, sizeof(amount));
				break;
			case EmmiterSpawnModule::EmmiterSpawnModuleType::CONSTANT_BURST:
				spawnRate = (*i)->spawnModule->getSpawnRate();
				oFile.write((char*)&spawnRate, sizeof(spawnRate));
				amount = (*i)->spawnModule->getAmount();
				oFile.write((char*)&amount, sizeof(amount));
				break;
			default:
				break;
			}
		}
		else {
			moduleExistence = false;
			oFile.write((char*)&moduleExistence, sizeof(moduleExistence));
		}

		if ((*i)->renderModule) {
			moduleExistence = true;
			oFile.write((char*)&moduleExistence, sizeof(moduleExistence));

			oFile.write((char*)&(*i)->renderModule->type, sizeof((*i)->renderModule->type));


		}
		else {
			moduleExistence = false;
			oFile.write((char*)&moduleExistence, sizeof(moduleExistence));
		}

		vLength = (*i)->initializeModules.size();

		for (auto j = (*i)->initializeModules.begin(); j != (*i)->initializeModules.end(); ++j) {
			oFile.write((char*)&j->get()->type, sizeof(j->get()->type));

			SingleOrRandom<vec3> vector = j->get()->getVector();
			oFile.write((char*)&vector, sizeof(vector));
		}

		vLength = (*i)->updateModules.size();

		for (auto j = (*i)->updateModules.begin(); j != (*i)->updateModules.end(); ++j) {
			oFile.write((char*)&j->get()->type, sizeof(j->get()->type));

		}

		oFile.write((char*)&(*i)->delay, sizeof((*i)->delay));

		oFile.write((char*)&(*i)->duration, sizeof((*i)->duration));

		oFile.write((char*)&(*i)->delay, sizeof((*i)->delay));

		oFile.write((char*)&(*i)->lifetime, sizeof((*i)->lifetime));

		oFile.write((char*)&(*i)->maxParticles, sizeof((*i)->maxParticles));

		oFile.write((char*)&(*i)->isLooping, sizeof((*i)->isLooping));
	}


	oFile.close();
}

void ParticleSystemComponent::Load()
{

}

bool ParticleSystemComponent::IsON()
{
	return isON;
}
