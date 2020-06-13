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

	pUpdateVertexBuffer = malloc(sizeof(void*));
	pUpdateVertexBuffer = memory->UpdateVertexBuffer;

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

	

	unsigned int indices4[] = { 0, 1, 2, 3, 2, 1 };
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[0].pIndexBuffer
		= createIndexBuffer(indices4, NELEMS(indices4));
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[0].numIndices
		= NELEMS(indices4);

	Rect tw1 = getFontMeshRect(&font_Arial, '0');
	Rect uvm1 = getFontUV(&font_Arial, '0');
	
	SimpleVertexCombined fvb[] = {
		{{tw1.L,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.L, uvm1.T}},
		{{tw1.R,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.R, uvm1.T}},
		{{tw1.L, -0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.L, uvm1.B}},
		{{tw1.R, -0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.R, uvm1.B}},
	};
	
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[0].pVertexBuffer
		= createVertexBuffer(fvb, NELEMS(fvb));

	TraslationComponent t4 = { 0 };
	t4.x = 0.5;
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


	Rect tw2 = getFontMeshRect(&font_Arial, '0');
	Rect uvm2 = getFontUV(&font_Arial, '0');

	SimpleVertexCombined fvb2[] = {
		{{tw2.L,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.L, uvm2.T}},
		{{tw2.R,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.R, uvm2.T}},
		{{tw2.L, -0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.L, uvm2.B}},
		{{tw2.R, -0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.R, uvm2.B}},
	};
	
	archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[1].pVertexBuffer = 
		createVertexBuffer(fvb2, NELEMS(fvb2));

	TraslationComponent t5 = { 0 };
	t5.x = -0.5;
	t5.y = 1;
	t5.z = -5.15;

	archetypeFontRenderingComponentTraslationScoreComponent->translations[1] = t5;
	archetypeFontRenderingComponentTraslationScoreComponent->scores[1] = 0;
}

void_pGameMemory(Update) {
    runSystems();
}