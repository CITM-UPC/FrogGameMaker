#pragma once
#include "EmmiterModule.h"
#include "Billboard.h"

class BillboardRender : public EmmiterRenderModule {
public:
	BillboardRender(Emmiter* owner);

	BillboardType type;

	void Update(Particle* particle, vec3 cameraPosition) override;
};