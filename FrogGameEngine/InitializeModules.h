#pragma once
#include "EmmiterModule.h"
#include "SingleOrRandom.h"

class SetSpeed : public EmmiterInitializeModule {
public: 
	SetSpeed();

	void Initialize(Particle* particle);

	SingleOrRandom<vec3> speed;
};

class SetColor : public EmmiterInitializeModule {
public:
	SetColor(); 

	void Initialize(Particle* particle);

	SingleOrRandom<vec3> color;
};