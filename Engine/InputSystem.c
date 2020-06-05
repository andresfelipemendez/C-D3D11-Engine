#include "InputSystem.h"
#include "engine.h"
#include "InputComponent.h"
#include "EntityManager.h"

extern unsigned int* pNumEntitiesentitiesARTI;

void input_system()
{
	InputComponent ic = GetInput();
	InputComponent* p = archetypeRendererTraslationInput->inputComponents;
	TraslationComponent* t = archetypeRendererTraslationInput->traslationComponents;

	// i need to get the delta time!
	
	unsigned int numRenderingComponents = *pNumEntitiesentitiesARTI;

	if(ic.keyboard != 0) {
	}

	for (int i = 0; i < numRenderingComponents; i++)
	{
		InputComponent rc = (*p);
		TraslationComponent tc = (*t);

		if ((ic.keyboard & 8)) {
			t->y += 0.01f;
		}

		if ((ic.keyboard & 4)) {
			t->y -= 0.01f;
		}

		p++;
		t++;
	}

}