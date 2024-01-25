#include "BillboardingEM.h"

BillboardRender::BillboardRender(Emmiter* owner)
{
	this->owner = owner;
	type = NONE;
}

void BillboardRender::Update(Particle* particle)
{
	particle->Render();
}
