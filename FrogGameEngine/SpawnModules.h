#pragma once
#include "EmmiterModule.h"

class ConstantSpawnRate : public EmmiterSpawnModule {
public:
	ConstantSpawnRate(Emmiter* owner);

	float spawnRate;
	float timeFromLastSpawn;

	void Update(double dt) override;
};

class SingleBurstSpawn : public EmmiterSpawnModule {
public:
	SingleBurstSpawn(Emmiter* owner);

	float amount;

	bool activated = false;

	void Update(double dt) override;
};

class ConstantBurstSpawn : public EmmiterSpawnModule {
public:
	ConstantBurstSpawn(Emmiter* owner);

	float spawnRate;
	float timeFromLastSpawn;

	float amount;

	void Update(double dt) override;
};