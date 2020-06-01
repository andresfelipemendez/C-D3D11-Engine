#include "RenderingSystem.h"
#include "RenderingComponent.h"
#include "engine.h"

extern unsigned int * pNumRenderingComponents;
extern RenderingComponent* pRenderingComponents;

void renderingSystem(void)
{
	RenderingComponent* p = pRenderingComponents; 
	unsigned int numRenderingComponents = *pNumRenderingComponents;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		setBuffers(rc.numIndices, rc.pIndexBuffer, rc.pVertexBuffer);
		p++;
	}
}
