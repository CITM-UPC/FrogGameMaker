#include "SpawnModules.h"
#include "Emmiter.h"

ConstantSpawnRate::ConstantSpawnRate()
{
	spawnRate = 1;
	timeFromLastSpawn = 0;
}

void ConstantSpawnRate::Update(double dt)
{
	timeFromLastSpawn += dt;

	if (timeFromLastSpawn >= spawnRate) {
		int ticks = 0;

		while (timeFromLastSpawn >= spawnRate) {
			timeFromLastSpawn -= spawnRate;
			ticks++;
		}

		owner->SpawnParticles(ticks);
	}
}

void SingleBurstSpawn::Update(double dt)
{
	owner->SpawnParticles(amount);

	activated = false;
}

void ConstantBurstSpawn::Update(double dt)
{
	timeFromLastSpawn += dt;

	if (timeFromLastSpawn >= spawnRate) {
		int ticks = 0;

		while (timeFromLastSpawn >= spawnRate) {
			timeFromLastSpawn -= spawnRate;
			ticks++;
		}

		owner->SpawnParticles(ticks * amount);
	}
}
