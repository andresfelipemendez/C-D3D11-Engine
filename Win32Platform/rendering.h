#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <D3DX11async.h>
#include <D3DX10math.h>

#include "../Engine/engine.h"

typedef struct
{
    D3DXMATRIX world;
    D3DXMATRIX view;
    D3DXMATRIX projection;
} MatrixBufferType;

ID3D11Device* d3ddev;
ID3D11DeviceContext* d3dctx;
IDXGISwapChain* sc;

ID3D11Texture2D* d3dbb;
ID3D11RenderTargetView* view;

ID3D11InputLayout* m_layout;
ID3D11VertexShader* pVS;
ID3D11PixelShader* pPS;

//ID3D11Texture2D* pFontTexture = NULL;
ID3D11ShaderResourceView* m_texture;

static ID3D11Buffer* g_pIndexBuffer = NULL;
static ID3D11Buffer* g_pVertexBuffer = NULL;

ID3D11Buffer* m_matrixBuffer;

D3D11_MAPPED_SUBRESOURCE mappedResource;
MatrixBufferType *dataPtr;

D3DMATRIX viewMatrix, projectionMatrix, worldMatrix;
D3DMATRIX rotationMatrix;

unsigned int bufferNumber;

void InitMatrixTransform();

void* CreateIndexBuffer(unsigned int * indices, unsigned int size);
void* CreateVertexBuffer(SimpleVertexCombined* vertices, unsigned int size);

void CalculateMatrix(vector3 position);

void SetBuffers(vector3 pos, unsigned int numIndices, void* indexBuffer, void* vertexBuffer);