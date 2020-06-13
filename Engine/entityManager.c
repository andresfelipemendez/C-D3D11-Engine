#include "entityManager.h"
#include "stdlib.h"

static unsigned int numentitiesARRTI = 0;
unsigned int* pNumEntitiesARRTI = &numentitiesARRTI;

static unsigned int numentitiesARRTB = 0;
unsigned int* pNumEntitiesARRTB = &numentitiesARRTB;

static unsigned int numentitiesAFTS = 0;
unsigned int* pNumentitiesAFTS = &numentitiesAFTS;


void InitEntityManager(char* memory) 
{
	numentitiesARRTI = 2;
	numentitiesARRTB = 1;
	numentitiesAFTS = 2;

	archetypeRendererTraslationInput = memory;
	archetypeRendererTraslationInput->renderingComponents = NULL;
	archetypeRendererTraslationInput->translations= NULL;
	archetypeRendererTraslationInput->inputComponents = NULL;

	archetypeRendererTraslationInput->renderingComponents = 
		archetypeRendererTraslationInput + 1;

	archetypeRendererTraslationInput->rectangles =
		archetypeRendererTraslationInput->renderingComponents + numentitiesARRTI;

	archetypeRendererTraslationInput->translations = 
		archetypeRendererTraslationInput->rectangles + numentitiesARRTI;

	archetypeRendererTraslationInput->inputComponents =
		archetypeRendererTraslationInput->translations + numentitiesARRTI;

	archetypeRendererTraslationBounce = 
		archetypeRendererTraslationInput->inputComponents + numentitiesARRTI;

	archetypeRendererTraslationBounce->renderingComponents = 
		archetypeRendererTraslationBounce + 1;

	archetypeRendererTraslationBounce->translations =
		archetypeRendererTraslationBounce->renderingComponents + numentitiesARRTB;
	
	archetypeRendererTraslationBounce->bounceComponents =
		archetypeRendererTraslationBounce->translations + numentitiesARRTB;
	
	archetypeFontRenderingComponentTraslationScoreComponent = 
		archetypeRendererTraslationBounce->bounceComponents + numentitiesARRTB;

	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets = 
		archetypeFontRenderingComponentTraslationScoreComponent + 1;

	archetypeFontRenderingComponentTraslationScoreComponent->translations = 
		archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets + numentitiesAFTS;

	archetypeFontRenderingComponentTraslationScoreComponent->scores =
		archetypeFontRenderingComponentTraslationScoreComponent->translations + numentitiesAFTS;
}

