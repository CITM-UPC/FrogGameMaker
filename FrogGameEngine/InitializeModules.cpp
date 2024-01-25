#include "InitializeModules.h"

void SetSpeed::Initialize(Particle particle)
{
	if (speed.usingSingleValue) {
		particle.speed = speed.singleValue;
	}
	else {
		vec3 randomVec = vec3{ 
			randomFloat(speed.rangeValue.lowerLimit.x, speed.rangeValue.upperLimit.x), 
			randomFloat(speed.rangeValue.lowerLimit.y, speed.rangeValue.upperLimit.y), 
			randomFloat(speed.rangeValue.lowerLimit.z, speed.rangeValue.upperLimit.z) };

		particle.speed = randomVec;
	}

}
