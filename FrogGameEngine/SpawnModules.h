#pragma once
#include "EmmiterModule.h"

class ConstantSpawnRate : public EmmiterSpawnModule {
public:
	ConstantSpawnRate();

	float spawnRate;
	float timeFromLastSpawn;

	void Update(double dt) override;
};

class SingleBurstSpawn : public EmmiterSpawnModule {
public:
	SingleBurstSpawn();

	float amount;

	bool activated = false;

	void Update(double dt) override;
};

class ConstantBurstSpawn : public EmmiterSpawnModule {
public:
	ConstantBurstSpawn(); 

	float spawnRate;
	float timeFromLastSpawn;

	float amount;

	void Update(double dt) override;
};