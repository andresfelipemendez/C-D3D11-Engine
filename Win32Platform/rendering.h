#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <D3DX11async.h>
#include <D3DX10math.h>


ID3D11Device* d3ddev;
ID3D11DeviceContext* d3dctx;
IDXGISwapChain* sc;

ID3D11Texture2D* d3dbb;
ID3D11RenderTargetView* view;

ID3D11InputLayout* m_layout;
ID3D11VertexShader* pVS;
ID3D11PixelShader* pPS;

static ID3D11Buffer* g_pIndexBuffer = NULL;
static ID3D11Buffer* g_pVertexBuffer = NULL;

ID3D11Buffer* m_matrixBuffer;

void* CreateIndexBuffer(unsigned int * indices, unsigned int size);