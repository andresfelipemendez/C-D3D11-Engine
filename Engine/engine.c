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

void_pGameMemory(Start) 
{
	ptr = malloc(sizeof(void*));
	ptr = memory->Print;

	pCreateIndexBuffer = malloc(sizeof(void*));
	pCreateIndexBuffer = memory->CreateIndexBuffer;

	pCreateVertexBuffer = malloc(sizeof(void*));
	pCreateVertexBuffer = memory->CreateVertexBuffer;

	pSetBuffers = malloc(sizeof(void*));
	pSetBuffers = memory->SetBuffers;

	pGetInput = malloc(sizeof(void*));
	pGetInput = memory->getInput;

	InitEntityManager();
	InitSystemManager();
    
	registerSystem(renderingSystem);
	registerSystem(input_system);

	unsigned int entity = createEntityArchetiypeRendererTraslationInput();
	TraslationComponent t1 = {0};
	t1.x = 0;
	t1.y = 1;
	t1.z = -5.15;
	archetypeRendererTraslationInput->traslationComponents[entity] = t1;
	unsigned int indices[] = {3, 1, 0, 0, 1, 2};
	archetypeRendererTraslationInput->renderingComponents[entity].pIndexBuffer = createIndexBuffer(indices, NELEMS(indices));
	SimpleVertexCombined vertices[] = {
		{{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},

		{{-1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	};
	archetypeRendererTraslationInput->renderingComponents[entity].pVertexBuffer = createVertexBuffer(vertices, NELEMS(vertices));
    
	unsigned int entity2 = createEntityArchetiypeRendererTraslationInput();
	TraslationComponent t2 = {0};
	t2.x = 0;
	t2.y = -1;
	t2.z = -5.15;
	archetypeRendererTraslationInput->traslationComponents[entity2] = t2;

	unsigned int indices2[] = {1, 3, 0, 1, 0, 2};
	archetypeRendererTraslationInput->renderingComponents[entity2].pIndexBuffer = createIndexBuffer(indices2, NELEMS(indices2));
	SimpleVertexCombined vertices2[] = {
		{{0.9f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},

		{{0.9f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f,  1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		{{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}
	};
	archetypeRendererTraslationInput->renderingComponents[entity2].pVertexBuffer = createVertexBuffer(vertices2, NELEMS(vertices2));
}

void_pGameMemory(Update) {
    runSystems();
}