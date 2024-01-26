#pragma once
#include "EmmiterModule.h"
#include "SingleOrRandom.h"

class SetSpeed : public EmmiterInitializeModule {
public: 
	void Initialize(Particle* particle);

	SingleOrRandom<vec3> speed;
};

class SetColor : public EmmiterInitializeModule {
public:
	void Initialize(Particle* particle);

	SingleOrRandom<vec3> color;
};