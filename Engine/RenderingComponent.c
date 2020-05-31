#include "RenderingComponent.h"
#include "engine.h"

unsigned int CreateRenderingComponent(
	unsigned int* indices, unsigned int indicesLength, 
	SimpleVertexCombined* vertices, unsigned int verticesLength)
{
	createIndexBuffer(indices, indicesLength);

    return 0;
}
