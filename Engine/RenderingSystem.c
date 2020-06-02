#include "RenderingSystem.h"
#include "EntityManager.h"
#include "engine.h"

extern unsigned int* pNumEntitiesentitiesARTI;

void renderingSystem(void)
{
	RenderingComponent* p = archetypeRendererTraslationInput->renderingComponents; 
	unsigned int numRenderingComponents = *pNumEntitiesentitiesARTI;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		setBuffers(rc.numIndices, rc.pIndexBuffer, rc.pVertexBuffer);
		p++;
	}
}
