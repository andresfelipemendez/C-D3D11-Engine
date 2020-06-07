#pragma once

typedef struct {
	float Pos[3];
	float Col[3];
} SimpleVertexCombined;

typedef struct {
	unsigned int numIndices;
	void* pIndexBuffer;
	void* pVertexBuffer;
} RenderingComponent;