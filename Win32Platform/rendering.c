#include "rendering.h"
#include "../Engine/Components/RenderingComponent.h"

typedef struct Character {
	int codePoint, x, y, width, height, originX, originY;
} Character;

typedef struct Font {
	const char* name;
	int size, bold, italic, width, height, characterCount;
	Character* characters;
} Font;

static Character characters_Arial[] = {
  {' ', 237, 106, 3, 3, 1, 1},
  {'!', 120, 81, 7, 25, -1, 24},
  {'"', 148, 106, 11, 10, 0, 24},
  {'#', 284, 31, 20, 25, 1, 24},
  {'$', 108, 0, 18, 29, 0, 25},
  {'%', 183, 0, 28, 25, 0, 24},
  {'&', 92, 31, 22, 25, 0, 24},
  {'\'', 159, 106, 6, 10, 0, 24},
  {'(', 56, 0, 10, 31, -1, 24},
  {')', 66, 0, 10, 31, -1, 24},
  {'*', 135, 106, 13, 12, 0, 24},
  {'+', 84, 106, 18, 17, 0, 20},
  {',', 165, 106, 6, 10, -1, 4},
  {'-', 199, 106, 11, 5, 0, 11},
  {'.', 210, 106, 5, 5, -2, 4},
  {'/', 76, 81, 11, 25, 1, 24},
  {'0', 59, 56, 18, 25, 0, 24},
  {'1', 87, 81, 11, 25, -2, 24},
  {'2', 239, 56, 17, 25, 0, 24},
  {'3', 77, 56, 18, 25, 0, 24},
  {'4', 40, 56, 19, 25, 1, 24},
  {'5', 95, 56, 18, 25, 0, 24},
  {'6', 113, 56, 18, 25, 0, 24},
  {'7', 131, 56, 18, 25, 0, 24},
  {'8', 149, 56, 18, 25, 0, 24},
  {'9', 167, 56, 18, 25, 0, 24},
  {':', 43, 106, 5, 19, -2, 18},
  {';', 142, 81, 6, 24, -1, 18},
  {'<', 48, 106, 18, 18, 0, 20},
  {'=', 117, 106, 18, 12, 0, 17},
  {'>', 66, 106, 18, 18, 0, 20},
  {'?', 185, 56, 18, 25, 0, 24},
  {'@', 0, 0, 33, 31, 0, 24},
  {'A', 261, 0, 24, 25, 1, 24},
  {'B', 304, 31, 20, 25, -1, 24},
  {'C', 309, 0, 23, 25, 0, 24},
  {'D', 114, 31, 22, 25, -1, 24},
  {'E', 0, 56, 20, 25, -1, 24},
  {'F', 203, 56, 18, 25, -1, 24},
  {'G', 285, 0, 24, 25, 0, 24},
  {'H', 158, 31, 21, 25, -1, 24},
  {'I', 127, 81, 5, 25, -2, 24},
  {'J', 49, 81, 15, 25, 0, 24},
  {'K', 136, 31, 22, 25, -1, 24},
  {'L', 256, 56, 17, 25, -1, 24},
  {'M', 211, 0, 25, 25, -1, 24},
  {'N', 179, 31, 21, 25, -1, 24},
  {'O', 236, 0, 25, 25, 0, 24},
  {'P', 20, 56, 20, 25, -1, 24},
  {'Q', 126, 0, 25, 26, 0, 24},
  {'R', 0, 31, 23, 25, -1, 24},
  {'S', 200, 31, 21, 25, 0, 24},
  {'T', 221, 31, 21, 25, 1, 24},
  {'U', 242, 31, 21, 25, -1, 24},
  {'V', 23, 31, 23, 25, 1, 24},
  {'W', 151, 0, 32, 25, 1, 24},
  {'X', 46, 31, 23, 25, 1, 24},
  {'Y', 69, 31, 23, 25, 1, 24},
  {'Z', 263, 31, 21, 25, 1, 24},
  {'[', 76, 0, 9, 31, -1, 24},
  {'\\', 98, 81, 11, 25, 1, 24},
  {']', 85, 0, 9, 31, 1, 24},
  {'^', 102, 106, 15, 15, 0, 24},
  {'_', 215, 106, 22, 4, 2, -3},
  {'`', 190, 106, 9, 6, 0, 24},
  {'a', 198, 81, 18, 19, 0, 18},
  {'b', 273, 56, 17, 25, -1, 24},
  {'c', 306, 81, 17, 19, 0, 18},
  {'d', 290, 56, 17, 25, 0, 24},
  {'e', 216, 81, 18, 19, 0, 18},
  {'f', 64, 81, 12, 25, 1, 24},
  {'g', 307, 56, 17, 25, 0, 18},
  {'h', 17, 81, 16, 25, -1, 24},
  {'i', 132, 81, 5, 25, -1, 24},
  {'j', 94, 0, 9, 31, 3, 24},
  {'k', 33, 81, 16, 25, -1, 24},
  {'l', 137, 81, 5, 25, -1, 24},
  {'m', 148, 81, 25, 19, -1, 18},
  {'n', 323, 81, 16, 19, -1, 18},
  {'o', 234, 81, 18, 19, 0, 18},
  {'p', 324, 56, 17, 25, -1, 18},
  {'q', 0, 81, 17, 25, 0, 18},
  {'r', 32, 106, 11, 19, -1, 18},
  {'s', 0, 106, 16, 19, 0, 18},
  {'t', 109, 81, 11, 25, 1, 24},
  {'u', 16, 106, 16, 19, -1, 18},
  {'v', 252, 81, 18, 19, 1, 18},
  {'w', 173, 81, 25, 19, 1, 18},
  {'x', 270, 81, 18, 19, 1, 18},
  {'y', 221, 56, 18, 25, 1, 18},
  {'z', 288, 81, 18, 19, 1, 18},
  {'{', 45, 0, 11, 31, 0, 24},
  {'|', 103, 0, 5, 31, -2, 24},
  {'}', 33, 0, 12, 31, 1, 24},
  {'~', 171, 106, 19, 7, 0, 15},
};

static Font font_Arial = { "Arial", 32, 0, 0, 341, 125, 95, characters_Arial };

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

void CreateTexture() {
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = 341;
	desc.Height = 125;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;

	
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
