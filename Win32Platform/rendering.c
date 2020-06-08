#include "rendering.h"
#include "../Engine/Components/RenderingComponent.h"


void InitMatrixTransform() 
{	
	float fieldOfView = (float)PI / 4.0f;
	float screenAspect = (float)800 / (float)600;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, fieldOfView, screenAspect, 0.03f, 100.0f);

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	HRESULT result = d3ddev->lpVtbl->CreateBuffer(d3ddev, &matrixBufferDesc, NULL, &m_matrixBuffer);

	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	vector3 position = {0};
	position.x = 0;
	position.y = 0;
	position.z = 0;
	CalculateMatrix(position);
}

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

void* CreateVertexBuffer(SimpleVertexCombined* vertices, unsigned int size)
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(vertices[0]) * size;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	ID3D11Buffer* pVertexBuffer = 0;
	d3ddev->lpVtbl->CreateBuffer(d3ddev, &bufferDesc, NULL, &pVertexBuffer);

	unsigned int sovc = sizeof(vertices[0]) * size;
	D3D11_MAPPED_SUBRESOURCE ms;
	d3dctx->lpVtbl->Map(d3dctx, pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertices, sizeof(vertices[0]) * size);
	d3dctx->lpVtbl->Unmap(d3dctx, pVertexBuffer, NULL);

	return pVertexBuffer;
}

void CalculateMatrix(vector3 position) {
	vector3 up, lookAt;
	vector3 rot;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	rot.x = 0; //yaw
	rot.y = 0; //pitch
	rot.z = 0; //roll

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, rot.x, rot.y, rot.z);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	lookAt = add(position, lookAt);

	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
}

void SetBuffers(vector3 pos, unsigned int numIndices, void* indexBuffer, void* vertexBuffer) 
{
	CalculateMatrix(pos);

	HRESULT result = d3dctx->lpVtbl->Map(d3dctx, m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType *)mappedResource.pData;

	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	d3dctx->lpVtbl->Unmap(d3dctx, m_matrixBuffer, 0);
	bufferNumber = 0;
	d3dctx->lpVtbl->VSSetConstantBuffers(d3dctx, bufferNumber, 1, &m_matrixBuffer);

	unsigned int off = 0;
	unsigned int str = sizeof(SimpleVertexCombined);
	//d3dctx->lpVtbl->IASetIndexBuffer(d3dctx, indexBuffer, DXGI_FORMAT_R32_UINT, 0); // drawing triangle list
	d3dctx->lpVtbl->IASetVertexBuffers(d3dctx, 0, 1, &vertexBuffer, &str, &off);
	d3dctx->lpVtbl->IASetPrimitiveTopology(d3dctx, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dctx->lpVtbl->Draw(d3dctx, 6, 0);
}
