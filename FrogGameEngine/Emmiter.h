#pragma once
// holds the information on how the particles behave
// only one behavior
// loopable?
// duration?
// delay? (to put an emmiter after another)
// uses the transform of the game object the particle system component belongs
// ranges of values if random (template of ranges for random?)
// 
// maybe create a "component type" for specific behaviors and having them in a vector
// particle module in the powerpoints
// 
// list/vector of the particles

#include <vector>
#include <queue>
#include "Particle.h"

#include "EmmiterModule.h"

// instead of writing individually every time all of this, this is nested in a struct that stores the single value, the range value and which one you're using
template <typename T> 
struct SingleOrRandom {
	bool usingSingleValue;
	union {
		T singleValue;
		struct rangeValue {
			T lowerLimit;
			T upperLimit;
		};
	};
};

class Emmiter {
public:
	Emmiter();
	~Emmiter();

	void Start();
	void Update(double dt);
	void Render();

	void SpawnParticles(int amount);
	
	// function for when we change the maxParticles or when we start
	void RestartParticlePool();

	void InitializeParticle(Particle& particle);

public:
	int maxParticles;

	float duration;
	float lifetime;

	bool isLooping;

	// specific behaviors
	EmmiterSpawnModule spawnModule;

	std::vector<EmmiterInitializeModule> initializeModules;

	std::vector<EmmiterUpdateModule> updateModules;

	std::vector<EmmiterRenderModule> renderModules;


	// graphic / mesh / mesh + texture

	SingleOrRandom<vec3> initialPosition;
	SingleOrRandom<vec3> initialVelocity;
	SingleOrRandom<vec3> initialAcceleration;

	SingleOrRandom<vec3> initialRotation;
	SingleOrRandom<vec3> initialAngularVelocity;

	SingleOrRandom<vec3> initialScale;
	SingleOrRandom<vec3> finalScale;

	// SingleOrRandom<Color> initialColor;
	// SingleOrRandom<Color> endColor;

private: 
	std::vector<Particle> particles;
	std::vector<int> usingParticlesIDs;
	std::queue<int> freeParticlesIDs;

};