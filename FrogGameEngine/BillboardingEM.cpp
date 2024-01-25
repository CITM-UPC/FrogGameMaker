#include "BillboardingEM.h"

void Billboarding::Update(std::vector<Particle>& particles)
{
	for (auto i = particles.begin(); i != particles.end(); ++i) {
		(*i).Render();
	}
}
