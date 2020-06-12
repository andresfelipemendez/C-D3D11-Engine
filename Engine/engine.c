#include "engine.h"
#include "EntityManager.h"
#include "Systems/RenderingSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/BounceSystem.h"

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

	InitEntityManager(memory->memory);
	InitSystemManager();

	
	registerSystem(input_system);
	registerSystem(BounceSystem);
	registerSystem(RenderingSystem);
}

void_pGameMemory(Start) 
{
	TraslationComponent t1 = {0};
	t1.x = 2.5f;
	t1.y = 0;
	t1.z = -5.15;
	archetypeRendererTraslationInput->translations[0] = t1;
	unsigned int indices[] = { 0, 1, 2, 3, 2, 1};
	archetypeRendererTraslationInput->renderingComponents[0].numIndices
		= NELEMS(indices);
	archetypeRendererTraslationInput->renderingComponents[0].pIndexBuffer = 
		createIndexBuffer(indices, NELEMS(indices));
	SimpleVertexCombined vertices[] = {
		{{-0.1f,  1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{ 0.1f,  1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{-0.1f, -1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{ 0.1f, -1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
	};
	archetypeRendererTraslationInput->renderingComponents[0].pVertexBuffer = 
		createVertexBuffer(vertices, NELEMS(vertices));
    

	TraslationComponent t2 = {0};
	t2.x = -2.5;
	t2.y = 0;
	t2.z = -5.15;
	archetypeRendererTraslationInput->translations[1] = t2;

	unsigned int indices2[] = { 0, 1, 2, 3, 2, 1 };
	archetypeRendererTraslationInput->renderingComponents[1].numIndices
		= NELEMS(indices2);
	archetypeRendererTraslationInput->renderingComponents[1].pIndexBuffer =
		createIndexBuffer(indices2, NELEMS(indices2));
	SimpleVertexCombined vertices2[] = {
		{{-0.1f,  1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{ 0.1f,  1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{-0.1f, -1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{ 0.1f, -1.0f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
	};
	archetypeRendererTraslationInput->renderingComponents[1].pVertexBuffer 
		= createVertexBuffer(vertices2, NELEMS(vertices2));

	TraslationComponent t3 = { 0 };
	t3.x = 0;
	t3.y = 0;
	t3.z = -5.15;
	archetypeRendererTraslationBounce->translations[0] = t3;

	RectangleComponent rc = { 0 };
	rc.width = 1.0f;
	rc.height = 1.0f;
	archetypeRendererTraslationBounce->translations[0] = t3;

	BounceComponent bc = { 0 };
	bc.velocity.x = 0.02f;
	bc.velocity.y = -0.02f;
	
	archetypeRendererTraslationBounce->bounceComponents[0] = bc;

	unsigned int indices3[] = { 0, 1, 2, 3, 2, 1 };
	
	archetypeRendererTraslationBounce->renderingComponents[0].pIndexBuffer
		= createIndexBuffer(indices3, NELEMS(indices3));
	archetypeRendererTraslationBounce->renderingComponents[0].numIndices 
		= NELEMS(indices3);

	SimpleVertexCombined vertices3[] = {
		{{-0.1f,  0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,1}},
		{{ 0.1f,  0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {1,1}},
		{{-0.1f, -0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {0,0}},
		{{ 0.1f, -0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {1,0}},
	};	
	archetypeRendererTraslationBounce->renderingComponents[0].pVertexBuffer
		= createVertexBuffer(vertices3, NELEMS(vertices3));

	// ---------------

	;

	unsigned int indices4[] = { 0, 1, 2, 3, 2, 1 };
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[0].pIndexBuffer
		= createIndexBuffer(indices4, NELEMS(indices4));
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[0].numIndices
		= NELEMS(indices4);

	
	int idx = 20;
	UvMapping uvm1 = getuv(
		font_Arial.width, 
		font_Arial.height, 
		characters_Arial[idx].x,
		characters_Arial[idx].y,
		characters_Arial[idx].width,
		characters_Arial[idx].height
	);

	SimpleVertexCombined fvb[] = {
		{{-0.1f,  0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm1.B,uvm1.R}},
		{{ 0.1f,  0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm1.T,uvm1.R}},
		{{-0.1f, -0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm1.B,uvm1.L}},
		{{ 0.1f, -0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm1.T,uvm1.L}},
	};
	
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[0].pVertexBuffer
		= createVertexBuffer(fvb, NELEMS(fvb));

	TraslationComponent t4 = { 0 };
	t4.x = -0.5;
	t4.y = 1;
	t4.z = -5.15;
	archetypeFontRenderingComponentTraslationScoreComponent->translations[0] = t4;

	archetypeFontRenderingComponentTraslationScoreComponent->scores[0] = 0;

	// ---------------

	unsigned int indices5[] = { 0, 1, 2, 3, 2, 1 };
	archetypeFontRenderingComponentTraslationScoreComponent->
		fontRenderingComponets[1].pIndexBuffer
		= createIndexBuffer(indices5, NELEMS(indices5));
	archetypeFontRenderingComponentTraslationScoreComponent->
		fontRenderingComponets[1].numIndices
		= NELEMS(indices5);

	int idx2 = 1;
	UvMapping uvm2 = getuv(
		font_Arial.width,
		font_Arial.height,
		characters_Arial[idx2].x,
		characters_Arial[idx2].y,
		characters_Arial[idx2].width,
		characters_Arial[idx2].height
	);

	SimpleVertexCombined fvb2[] = {
		{{-0.1f,  0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm2.B,uvm2.R}},
		{{ 0.1f,  0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm2.T,uvm2.R}},
		{{-0.1f, -0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm2.B,uvm2.L}},
		{{ 0.1f, -0.1f, 0.0f}, {0.05f, 0.5f, 0.5f, 0.5f}, {uvm2.T,uvm2.L}},
	};
	
	archetypeFontRenderingComponentTraslationScoreComponent->
		fontRenderingComponets[1].pVertexBuffer
		= createVertexBuffer(fvb2, NELEMS(fvb2));

	TraslationComponent t5 = { 0 };
	t5.x = 0.5;
	t5.y = 1;
	t5.z = -5.15;

	archetypeFontRenderingComponentTraslationScoreComponent->translations[1] = t5;

	archetypeFontRenderingComponentTraslationScoreComponent->scores[1] = 0;

}

void_pGameMemory(Update) {
    runSystems();
}