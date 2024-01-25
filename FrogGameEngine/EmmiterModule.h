#pragma once
#include "Particle.h"
#include <vector>

class Emmiter;

class EmmiterSpawnModule {
public:
	virtual void Update(double dt) {};

protected:
	Emmiter* owner;
};

class EmmiterInitializeModule {
public:
	virtual void Initialize(Particle particle) {};

protected:
	Emmiter* owner;
};

class EmmiterUpdateModule {
public:
	virtual void Update(double dt, std::vector<Particle>& particles) {};

protected:
	Emmiter* owner;
};

class EmmiterRenderModule {
public:
	virtual void Update(std::vector<Particle>& particles) {};

protected:
	Emmiter* owner;
};