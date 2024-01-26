#pragma once
#include "Particle.h"
#include <vector>

class Emmiter;

class EmmiterSpawnModule {
public:
	virtual void Reset() {};

	virtual void Update(double dt) {};

	enum EmmiterSpawnModuleType {
		CONSTANT,
		SINGLE_BURST,
		CONSTANT_BURST
	};

	EmmiterSpawnModuleType type;

	float duration;

protected:
	Emmiter* owner;
};

class EmmiterInitializeModule {
public:
	virtual void Reset() {};

	virtual void Initialize(Particle* particle) {};

	enum EmmiterInitializeModuleType {
		SET_SPEED,
		SET_COLOR
	};

	EmmiterInitializeModuleType type;

protected:
	Emmiter* owner;
};

class EmmiterUpdateModule {
public:
	virtual void Reset() {};

	virtual void Update(double dt, Particle* particle) {};

	enum EmmiterUpdateModuleType {
		CHANGE_COLOR
	};

	EmmiterUpdateModuleType type;

protected:
	Emmiter* owner;
};

class EmmiterRenderModule {
public:
	virtual void Reset() {};

	virtual void Update(Particle* particle) {};

	enum EmmiterRenderModuleType {
		BILLBOARD
	};

	EmmiterRenderModuleType type;

protected:
	Emmiter* owner;
};