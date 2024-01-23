#include "Particle.h"

void Particle::Update(double dt)
{
	lifetime += dt;

	color += deltaColor * dt;

	position += velocity * dt;
}
