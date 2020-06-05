#include "InputSystem.h"
#include "engine.h"
#include "InputComponent.h"
#include "EntityManager.h"

extern unsigned int* pNumEntitiesentitiesARTI;

// i need to get the delta time!
void input_system()
{
	InputComponent ic = GetInput();
	InputComponent* p = archetypeRendererTraslationInput->inputComponents;
	TraslationComponent* t = archetypeRendererTraslationInput->translations;

	unsigned int numRenderingComponents = *pNumEntitiesentitiesARTI;

	if ((ic.keyboard & 8)) {
		t->y -= 0.01f;
	}

	if ((ic.keyboard & 4)) {
		t->y += 0.01f;
	}

	p++;
	t++;
	
	if ((ic.keyboard & 2)) {
		t->y -= 0.01f;
	}

	if ((ic.keyboard & 1)) {
		t->y += 0.01f;
	}

}
									       