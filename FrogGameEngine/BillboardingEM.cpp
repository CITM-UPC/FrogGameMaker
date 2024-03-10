#include "BillboardingEM.h"
#include "Emmiter.h"
#include "ParticleSystemComponent.h"
#include "TransformComponent.h"
#include "Billboard.h"
#include "GL/glew.h"

BillboardRender::BillboardRender(Emmiter* owner)
{
	this->owner = owner;
	type = NONE;
}

void BillboardRender::Update(Particle* particle, vec3 cameraPosition)
{
	vec3 particlePosition = particle->position + owner->owner->GetTransform()->getPosition();

	Billboard::BeginCylindricBillboard(particlePosition, cameraPosition);

    // render
    glBegin(GL_TRIANGLES);
    glColor3ub(particle->color.r, particle->color.g, particle->color.b);

    glVertex3d(particle->position.x - (1 * particle->scale.x), particle->position.y + (1 * particle->scale.y), particle->position.z);
    glVertex3d(particle->position.x - (1 * particle->scale.x), particle->position.y - (1 * particle->scale.y), particle->position.z);
    glVertex3d(particle->position.x + (1 * particle->scale.x), particle->position.y + (1 * particle->scale.y), particle->position.z);

    glVertex3d(particle->position.x - (1 * particle->scale.x), particle->position.y - (1 * particle->scale.y), particle->position.z);
    glVertex3d(particle->position.x + (1 * particle->scale.x), particle->position.y - (1 * particle->scale.y), particle->position.z);
    glVertex3d(particle->position.x + (1 * particle->scale.x), particle->position.y + (1 * particle->scale.y), particle->position.z);

    glEnd();

	// particle->Render();

	Billboard::EndBillboard();

}
