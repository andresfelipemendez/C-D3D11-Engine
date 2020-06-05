#include "entityManager.h"

static void* entitiesARTI[512];
static unsigned int numentitiesARTI = 0;
unsigned int* pNumEntitiesentitiesARTI = &numentitiesARTI;

void InitEntityManager() {
	archetypeRendererTraslationInput = malloc(sizeof(void*));
	archetypeRendererTraslationInput->renderingComponents = malloc(sizeof(RenderingComponent) * 512);
	archetypeRendererTraslationInput->translations = malloc(sizeof(TraslationComponent) * 512);
	archetypeRendererTraslationInput->inputComponents = malloc(sizeof(InputComponent) * 512);
}


unsigned int createEntityArchetiypeRendererTraslationInput()
{
	if(numentitiesARTI >= 512) {
		// todo fail or expand
		return 0;
	}

	return numentitiesARTI++;
}
