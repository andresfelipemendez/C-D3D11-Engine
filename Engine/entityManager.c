#include "entityManager.h"
#include "stdlib.h"

static unsigned int numentitiesARRTI = 0;
unsigned int* pNumEntitiesARRTI = &numentitiesARRTI;

static unsigned int numentitiesARRTB = 0;
unsigned int* pNumEntitiesARRTB = &numentitiesARRTB;

void InitEntityManager(char* memory) 
{
	archetypeRendererTraslationInput = memory;
	archetypeRendererTraslationInput->renderingComponents = NULL;
	archetypeRendererTraslationInput->translations= NULL;
	archetypeRendererTraslationInput->inputComponents = NULL;

	archetypeRendererTraslationInput->renderingComponents = 
		archetypeRendererTraslationInput + 1;

	archetypeRendererTraslationInput->rectangles =
		archetypeRendererTraslationInput->renderingComponents + 2;

	archetypeRendererTraslationInput->translations = 
		archetypeRendererTraslationInput->rectangles + 2;

	archetypeRendererTraslationInput->inputComponents =
		archetypeRendererTraslationInput->translations + 2;


	archetypeRendererTraslationBounce = 
		archetypeRendererTraslationInput->inputComponents + 2;

	archetypeRendererTraslationBounce->renderingComponents = NULL;
	archetypeRendererTraslationBounce->translations = NULL;
	archetypeRendererTraslationBounce->bounceComponents = NULL;

	archetypeRendererTraslationBounce->renderingComponents = 
		archetypeRendererTraslationBounce + 1;

	archetypeRendererTraslationBounce->translations =
		archetypeRendererTraslationBounce->renderingComponents + 1;
	
	archetypeRendererTraslationBounce->bounceComponents =
		archetypeRendererTraslationBounce->translations + 1;

	// todo change constants for this
	numentitiesARRTI = 2;
	numentitiesARRTB = 1;
}

