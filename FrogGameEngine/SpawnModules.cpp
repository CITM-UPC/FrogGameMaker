#include "SpawnModules.h"
#include "Emmiter.h"

ConstantSpawnRate::ConstantSpawnRate(Emmiter* owner)
{
	this->owner = owner;
	spawnRate = 0.5f;
	timeFromLastSpawn = 0;
}

void ConstantSpawnRate::Update(double dt)
{
	if (spawnRate <= 0.001) return;

	timeFromLastSpawn += dt;

	if (timeFromLastSpawn >= 1 / spawnRate) {
		int ticks = 0;

		while (timeFromLastSpawn >= 1 / spawnRate) {
			timeFromLastSpawn -= 1 / spawnRate;
			ticks++;
		}

		owner->SpawnParticles(ticks);
	}
}

SingleBurstSpawn::SingleBurstSpawn(Emmiter* owner)
{
	this->owner = owner;
	amount = 10;
}

void SingleBurstSpawn::Update(double dt)
{
	owner->SpawnParticles(amount);

	activated = false;
}

ConstantBurstSpawn::ConstantBurstSpawn(Emmiter* owner)
{
	this->owner = owner;
	spawnRate = 0.5f;
	timeFromLastSpawn = 0;
	amount = 10;
}

void ConstantBurstSpawn::Update(double dt)
{
	if (spawnRate <= 0.001) return;

	timeFromLastSpawn += dt;

	if (timeFromLastSpawn >= 1 / spawnRate) {
		int ticks = 0;

		while (timeFromLastSpawn >= 1 / spawnRate) {
			timeFromLastSpawn -= 1 / spawnRate;
			ticks++;
		}

		owner->SpawnParticles(ticks * amount);
	}
}
