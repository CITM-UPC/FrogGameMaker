#pragma once
#include "EmmiterModule.h"

class ConstantSpawnRate : public EmmiterSpawnModule {
public:
	ConstantSpawnRate(Emmiter* owner);

	float spawnRate;
	float timeFromLastSpawn;

	const float getSpawnRate() override {
		return spawnRate;
	};

	void Update(double dt) override;
};

class SingleBurstSpawn : public EmmiterSpawnModule {
public:
	SingleBurstSpawn(Emmiter* owner);

	float amount;

	bool activated;

	const float getAmount() override {
		return amount;
	};

	void Reset() override;

	void Update(double dt) override;
};

class ConstantBurstSpawn : public EmmiterSpawnModule {
public:
	ConstantBurstSpawn(Emmiter* owner);

	float spawnRate;
	float timeFromLastSpawn;

	float amount;

	const float getSpawnRate() override {
		return spawnRate;
	};
	const float getAmount() override {
		return amount;
	};

	void Update(double dt) override;
};