#pragma once
// maybe should be component
// has a vector of emmiters
// can be saved and loaded to file

#include "Component.h"
#include "Emmiter.h"
#include <vector>

class ParticleSystemComponent : public Component {

public:
	ParticleSystemComponent(GameObject* owner);
	~ParticleSystemComponent();

	void Update() override;
	void Render() override;

	std::vector<Emmiter> emmiters;

protected:

private:

};