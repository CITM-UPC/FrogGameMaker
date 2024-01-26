#include "BillboardingEM.h"
// #include "GL/glew.h"

BillboardRender::BillboardRender(Emmiter* owner)
{
	this->owner = owner;
	type = NONE;
}

void BillboardRender::Update(Particle* particle)
{
	// try for making it global
	// glPushMatrix();
	// glLoadIdentity();

	// try for making the billboarding
	// GLfloat projection[16];
	// glGetFloatv(GL_PROJECTION_MATRIX, projection);

	particle->Render();

	// glPopMatrix();
}
