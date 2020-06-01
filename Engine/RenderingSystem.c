#include "RenderingSystem.h"
#include "RenderingComponent.h"
#include "engine.h"

extern unsigned int * pNumRenderingComponents;
extern RenderingComponent* pRenderingComponents;

void renderingSystem(void)
{
	RenderingComponent* p = pRenderingComponents; 
	for (int i = 0; i < *pNumRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		void* indexBuffer = rc.pIndexBuffer;
		void* vertexBuffer = rc.pVertexBuffer;
		setBuffers(indexBuffer, vertexBuffer);
		p++;

	}
}
