#include "RenderingSystem.h"
#include "EntityManager.h"
#include "engine.h"

extern unsigned int* pNumEntitiesentitiesARTI;

void renderingSystem(void)
{
	RenderingComponent* p = archetypeRendererTraslationInput->renderingComponents; 
	TraslationComponent* t = archetypeRendererTraslationInput->translations; 

	unsigned int numRenderingComponents = *pNumEntitiesentitiesARTI;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		TraslationComponent tc = (*t);
		vector3 pos = {0};
		pos.x = tc.x;
		pos.y = tc.y;
		pos.z = tc.z;
		setBuffers(pos, rc.numIndices, rc.pIndexBuffer, rc.pVertexBuffer);
		p++;
		t++;
	}
}
