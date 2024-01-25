#pragma once
#include "EmmiterModule.h"

class Billboarding : public EmmiterRenderModule {
public:
	enum BillboardType {
		NONE,
		SCREEN_ALIGNED,
		VIEWPORT_ORIENTED,
		AXIS_ALIGNED
	};

	BillboardType type;

	void Update(Particle* particle) override;
};