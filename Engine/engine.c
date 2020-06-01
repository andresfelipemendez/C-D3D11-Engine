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

    //Add Entity
    unsigned int indices[] = {0, 1, 2};
	SimpleVertexCombined verticesCombo[] = {
		{{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.5f}},
		{{0.5f, -0.5f, 0.0f}, {0.5f, 0.0f, 0.5f}},
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.5f}}
	};

	CreateRenderingComponent(indices, NELEMS(indices), verticesCombo, NELEMS(verticesCombo));

    

    registerSystem(renderingSystem);
}

void_pGameMemory(Update) {
    runSystems();
}