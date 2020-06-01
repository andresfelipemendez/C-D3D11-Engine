#pragma once

typedef struct {
	float Pos[3];
	float Col[3];
} SimpleVertexCombined;

typedef struct {
	void* pIndexBuffer;
	void* pVertexBuffer;
} RenderingComponent;

unsigned int CreateRenderingComponent(unsigned int* indices, unsigned int indicesLength, 
									  SimpleVertexCombined* vertices, unsigned int verticesLength);