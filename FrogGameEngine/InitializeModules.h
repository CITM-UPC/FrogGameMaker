#pragma once
#include "EmmiterModule.h"
#include "SingleOrRandom.h"

class SetSpeed : public EmmiterInitializeModule {
public: 
	SetSpeed();

	const SingleOrRandom<vec3> getVector() {
		return speed;
	};

	void Initialize(Particle* particle);

	SingleOrRandom<vec3> speed;
};

class SetColor : public EmmiterInitializeModule {
public:
	SetColor(); 

	const SingleOrRandom<vec3> getVector() {
		return color;
	};

	void Initialize(Particle* particle);

	SingleOrRandom<vec3> color;
};