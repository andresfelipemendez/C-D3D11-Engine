#include "RenderingSystem.h"
#include "../EntityManager.h"
#include "../engine.h"

extern unsigned int* pNumEntitiesARRTI;
extern unsigned int* pNumEntitiesARRTB;

void RenderingSystem(void)
{
	RenderingComponent* p = archetypeRendererTraslationInput->renderingComponents; 
	TraslationComponent* t = archetypeRendererTraslationInput->translations; 
	unsigned int numRenderingComponents = *pNumEntitiesARRTI;
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

	p = archetypeRendererTraslationBounce->renderingComponents;
	t = archetypeRendererTraslationBounce->translations;
	numRenderingComponents = *pNumEntitiesARRTB;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		TraslationComponent tc = (*t);
		vector3 pos = { 0 };
		pos.x = tc.x;
		pos.y = tc.y;
		pos.z = tc.z;
		setBuffers(pos, rc.numIndices, rc.pIndexBuffer, rc.pVertexBuffer);
		p++;
		t++;
	}

}
