#pragma once
#include "EmmiterModule.h"

class BillboardRender : public EmmiterRenderModule {
public:
	BillboardRender(Emmiter* owner);

	enum BillboardType {
		NONE,
		SCREEN_ALIGNED,
		VIEWPORT_ORIENTED,
		AXIS_ALIGNED
	};

	BillboardType type;

	void Update(Particle* particle) override;
};