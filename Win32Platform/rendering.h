#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#include "../Engine/engine.h"

#include "mathlib.h"
#include "dds_loader.h"

typedef struct
{
    Mat4 world;
    Mat4 view;
    Mat4 projection;
} MatrixBufferType;

ID3D11Device* d3ddev;
ID3D11DeviceContext* d3dctx;
IDXGISwapChain* sc;

ID3D11Texture2D* d3dbb;
ID3D11RenderTargetView* view;

ID3D11InputLayout* m_layout;
ID3D11VertexShader* pVS;
ID3D11PixelShader* pPS;

ID3D11ShaderResourceView* m_texture;
ID3D11SamplerState* m_sampleState;

static ID3D11Buffer* g_pIndexBuffer = NULL;
static ID3D11Buffer* g_pVertexBuffer = NULL;

ID3D11Buffer* m_matrixBuffer;

D3D11_MAPPED_SUBRESOURCE mappedResource;
MatrixBufferType *dataPtr;

Mat4 viewMatrix, projectionMatrix, worldMatrix;
Mat4 rotationMatrix;

unsigned int bufferNumber;

void InitMatrixTransform();

void* CreateIndexBuffer(unsigned int * indices, unsigned int size);
void* UpdateVertexBuffer(void* vertexBuffer, SimpleVertexCombined* vertices, unsigned int size);
void* CreateVertexBuffer(SimpleVertexCombined* vertices, unsigned int size);

void CalculateMatrix(vector3 position);

void SetBuffers(vector3 pos, unsigned int numIndices, void* indexBuffer, void* vertexBuffer);