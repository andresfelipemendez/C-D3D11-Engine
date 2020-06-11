#pragma once

typedef struct {
	float Pos[3];
	float Col[4];
	float Tex[2];
} SimpleVertexCombined;

typedef struct {
	unsigned int numIndices;
	void* pIndexBuffer;
	void* pVertexBuffer;
} RenderingComponent;