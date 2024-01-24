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
#include <array>
#include "Particle.h"
#include <memory>

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
	bool isON;

	int maxParticles;

	float duration;
	float lifetime;

	float delay;

	bool isLooping;

	// specific behaviors
	std::unique_ptr<EmmiterSpawnModule> spawnModule;

	std::vector<std::unique_ptr<EmmiterInitializeModule>> initializeModules;

	std::vector<std::unique_ptr<EmmiterUpdateModule>> updateModules;

	std::unique_ptr<EmmiterRenderModule> renderModule;


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