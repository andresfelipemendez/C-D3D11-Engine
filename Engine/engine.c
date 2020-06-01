#include "engine.h"
#include "RenderingSystem.h"

vector3 add(vector3 a, vector3 b)
{
    vector3 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

void_pGameMemory(Start) {

    ptr = malloc(sizeof(void*));
    ptr = memory->Print;

    pCreateIndexBuffer = malloc(sizeof(void*));
    pCreateIndexBuffer = memory->CreateIndexBuffer;

	pCreateVertexBuffer = malloc(sizeof(void*));
	pCreateVertexBuffer = memory->CreateVertexBuffer;

    pSetBuffers = malloc(sizeof(void*));
    pSetBuffers = memory->SetBuffers;

    initSystemManager();

    unsigned int indices[] = {3, 1, 0, 0, 1, 2};

	SimpleVertexCombined verticesCombo[] = {
		{{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        {{-0.9f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	};

	CreateRenderingComponent(indices, NELEMS(indices), verticesCombo, NELEMS(verticesCombo));

	
    unsigned int indices2[] = {1, 3, 0, 1, 0, 2};

	SimpleVertexCombined verticesCombo2[] = {
		{{1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{0.9f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	};

    CreateRenderingComponent(indices2, NELEMS(indices2), verticesCombo2, NELEMS(verticesCombo2));

    registerSystem(renderingSystem);
}

void_pGameMemory(Update) {
    runSystems();
}