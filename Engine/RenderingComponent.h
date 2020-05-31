#pragma once

typedef struct {
	float Pos[3];
	float Col[3];
} SimpleVertexCombined;

typedef struct {
	void* indexBuffer;
	void* vertexBuffer;
} RenderingComponent;


static RenderingComponent* renderingComponentsArr = 0;

unsigned int CreateRenderingComponent(unsigned int* indices, unsigned int indicesLength, 
									  SimpleVertexCombined* vertices, unsigned int verticesLength);