#pragma once
// maybe should be component
// has a vector of emmiters
// can be saved and loaded to file

#include "Component.h"
#include "Emmiter.h"
#include <vector>
#include "TransformComponent.h"

class ParticleSystemComponent : public Component {

public:
	ParticleSystemComponent(GameObject* owner);
	~ParticleSystemComponent();

	void Update(double dt) override;
	void Render(vec3 cameraPosition);

	void Play();
	void Stop();
	void Replay();

	void ClearEmmiters();
	Emmiter* AddEmmiter();

	void Save();
	void Load(std::string path);

	bool IsON();

	TransformComponent* GetTransform();

	std::vector<std::unique_ptr<Emmiter>> emmiters;

protected:

private:
	TransformComponent* transform;

	bool isON;
};