#include "engine.h"
#include "EntityManager.h"
#include "RenderingSystem.h"
#include "InputSystem.h"


vector3 add(vector3 a, vector3 b)
{
    vector3 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

void_pGameMemory(SetMethodPointers)
{
	if (ptr == 0) {
		ptr = malloc(sizeof(void*));
	}
	ptr = memory->Print;

	if (pCreateIndexBuffer == 0) {
		pCreateIndexBuffer = malloc(sizeof(void*));
	}
	pCreateIndexBuffer = memory->CreateIndexBuffer;

	
	if (pCreateVertexBuffer == 0) {
		pCreateVertexBuffer = malloc(sizeof(void*));
	}
	pCreateVertexBuffer = memory->CreateVertexBuffer;

	if (pSetBuffers == 0) {
		pSetBuffers = malloc(sizeof(void*));
	}
	pSetBuffers = memory->SetBuffers;

	if (pGetInput == 0) {
		pGetInput = malloc(sizeof(void*));
	}
	pGetInput = memory->getInput;

	InitSystemManager();

	registerSystem(renderingSystem);
	registerSystem(input_system);

	InitEntityManager(memory->memory);
}

void_pGameMemory(Start) 
{

	TraslationComponent t1 = {0};
	t1.x = 0;
	t1.y = 1;
	t1.z = -5.15;
	archetypeRendererTraslationInput->translations[0] = t1;
	unsigned int indices[] = {3, 1, 0, 0, 1, 2};
	archetypeRendererTraslationInput->renderingComponents[0].pIndexBuffer = createIndexBuffer(indices, NELEMS(indices));
	SimpleVertexCombined vertices[] = {
		{{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},

		{{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	};
	archetypeRendererTraslationInput->renderingComponents[0].pVertexBuffer = createVertexBuffer(vertices, NELEMS(vertices));
    

	TraslationComponent t2 = {0};
	t2.x = 0;
	t2.y = -1;
	t2.z = -5.15;
	archetypeRendererTraslationInput->translations[1] = t2;

	unsigned int indices2[] = {1, 3, 0, 1, 0, 2};
	archetypeRendererTraslationInput->renderingComponents[1].pIndexBuffer = createIndexBuffer(indices2, NELEMS(indices2));
	SimpleVertexCombined vertices2[] = {
		{{0.9f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},

		{{0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	};
	archetypeRendererTraslationInput->renderingComponents[1].pVertexBuffer = createVertexBuffer(vertices2, NELEMS(vertices2));
}

void_pGameMemory(Update) {
    runSystems();
}