#include "engine.h"
#include "EntityManager.h"
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

    InitEntityManager();
    InitSystemManager();
    
    registerSystem(renderingSystem);

	unsigned int entity = createEntityArchetiypeRendererTraslationInput();
    archetypeRendererTraslationInput->traslationComponents[entity].x = 23;
    archetypeRendererTraslationInput->traslationComponents[entity].y = 23;
    archetypeRendererTraslationInput->traslationComponents[entity].z = 23;
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
    

	//traslation t1 = {0};


    //traslation t2 = {0};

    unsigned int entity2 = createEntityArchetiypeRendererTraslationInput();
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