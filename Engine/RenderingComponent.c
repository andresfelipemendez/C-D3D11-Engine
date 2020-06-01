#include "RenderingComponent.h"
#include "engine.h"

static unsigned int nrcs = 0;
unsigned int* pNumRenderingComponents = &nrcs;

static RenderingComponent renderingComponents[512];
RenderingComponent* pRenderingComponents= renderingComponents;

unsigned int CreateRenderingComponent(
	unsigned int* indices, unsigned int indicesLength, 
	SimpleVertexCombined* vertices, unsigned int verticesLength)
{
	renderingComponents[nrcs].numIndices = indicesLength;
	renderingComponents[nrcs].pIndexBuffer = createIndexBuffer(indices, indicesLength);
	renderingComponents[nrcs].pVertexBuffer = createVertexBuffer(vertices, verticesLength);
	nrcs++;
    return 0;
}
