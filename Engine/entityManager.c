#include "entityManager.h"
#include "stdlib.h"

static unsigned int numentitiesARTI = 0;
unsigned int* pNumEntitiesARTI = &numentitiesARTI;

static unsigned int numentitiesARTC = 0;
unsigned int* pNumEntitiesARTC = &numentitiesARTI;

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

