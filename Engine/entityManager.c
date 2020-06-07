#include "entityManager.h"
#include "stdlib.h"


static void* entitiesARTI[512];
static unsigned int numentitiesARTI = 0;
unsigned int* pNumEntitiesentitiesARTI = &numentitiesARTI;

void InitEntityManager(char* memory) 
{
	archetypeRendererTraslationInput = memory;

	archetypeRendererTraslationInput->renderingComponents = NULL;
	archetypeRendererTraslationInput->translations= NULL;
	archetypeRendererTraslationInput->inputComponents = NULL;

	archetypeRendererTraslationInput->renderingComponents = 
		archetypeRendererTraslationInput + 1;

	archetypeRendererTraslationInput->translations = 
		archetypeRendererTraslationInput->renderingComponents + 3;

	archetypeRendererTraslationInput->inputComponents =
		archetypeRendererTraslationInput->translations + 3;

	numentitiesARTI = 2;
}

