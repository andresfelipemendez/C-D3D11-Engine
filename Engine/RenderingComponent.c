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


	renderingComponents[nrcs].pIndexBuffer = createIndexBuffer(indices, indicesLength);
	renderingComponents[nrcs].pVertexBuffer = createVertexBuffer(vertices, verticesLength);

	//renderingComponents[numRenderingComponents].indexBuffer = indexBuffer;
	//renderingComponents[numRenderingComponents].vertexBuffer = vertexBuffer;
	nrcs++;
    return 0;
}



//static void* indexBuffers[512];
//void** pIndexBuffers = &indexBuffers;
//
//static void* vertexBuffers[512];
//void** pvertexBuffers = &vertexBuffers;