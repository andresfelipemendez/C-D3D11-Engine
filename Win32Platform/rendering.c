#include "rendering.h"

void* CreateIndexBuffer(unsigned int* indices, unsigned int size)
{

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(unsigned int) * size;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	ID3D11Buffer* pIndexBuffer = 0;
	d3ddev->lpVtbl->CreateBuffer(d3ddev, &bufferDesc, &InitData, &pIndexBuffer);

	return pIndexBuffer;
}

void* CreateVertexBuffer(unsigned int* vertices, unsigned int size)
{
	//D3D11_BUFFER_DESC bufferDesc;
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(vertices[0]) * 3;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//D3D11_SUBRESOURCE_DATA InitData;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	ID3D11Buffer* pVertexBuffer = 0;
	d3ddev->lpVtbl->CreateBuffer(d3ddev, &bufferDesc, NULL, &pVertexBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	d3dctx->lpVtbl->Map(d3dctx, pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertices, sizeof(vertices[0]) * size);
	d3dctx->lpVtbl->Unmap(d3dctx, pVertexBuffer, NULL);

	return pVertexBuffer;
}

void SetBuffers(void* indexBuffer, void* vertexBuffer) {
	int i = 0;
}