#include "RenderingSystem.h"

#include "../EntityManager.h"
#include "../engine.h"

extern unsigned int* pNumEntitiesARRTI;
extern unsigned int* pNumEntitiesARRTB;
extern unsigned int* pNumentitiesAFTS;

void RenderingSystem(void)
{
	RenderingComponent* p = archetypeRendererTraslationInput->renderingComponents; 
	TraslationComponent* t = archetypeRendererTraslationInput->translations; 
	unsigned int numRenderingComponents = *pNumEntitiesARRTI;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		TraslationComponent tc = (*t);
		vector3 pos = {0};
		pos.x = tc.x;
		pos.y = tc.y;
		pos.z = tc.z;
		setBuffers(pos, rc.numIndices, rc.pIndexBuffer, rc.pVertexBuffer);
		p++;
		t++;
	}

	p = archetypeRendererTraslationBounce->renderingComponents;
	t = archetypeRendererTraslationBounce->translations;
	numRenderingComponents = *pNumEntitiesARRTB;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		RenderingComponent rc = (*p);
		TraslationComponent tc = (*t);
		vector3 pos = { 0 };
		pos.x = tc.x;
		pos.y = tc.y;
		pos.z = tc.z;
		setBuffers(pos, rc.numIndices, rc.pIndexBuffer, rc.pVertexBuffer);
		p++;
		t++;
	}

	FontRenderingComponent* f = archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets;
	t = archetypeFontRenderingComponentTraslationScoreComponent->translations;

	numRenderingComponents = *pNumentitiesAFTS;
	for (int i = 0; i < numRenderingComponents; i++)
	{
		FontRenderingComponent fc = (*f);
		TraslationComponent tc = (*t);
		vector3 pos = { 0 };
		pos.x = tc.x;
		pos.y = tc.y;
		pos.z = tc.z;
		setBuffers(pos, fc.numIndices, fc.pIndexBuffer, fc.pVertexBuffer);
		f++;
		t++;
	}
}

Rect getFontMeshRect(Font* font, char c)
{
	Character cr = characters_Arial[((int)c) - 32];
	float w = (0.2 * cr.width) / cr.height;
	
	Rect uvm = { 0 };
	uvm.L = w / -2;
	uvm.R = w / 2;
	uvm.T = -0.1f;
	uvm.B = -0.1f;
	return uvm;
}

Rect getFontUV(Font* font, char c) 
{
	float textureWidth = font->width;
	float textureHeight = font->height;

	Character cr = characters_Arial[((int) c) - 32];

	Rect uvm = {0};
	uvm.L = cr.x /  textureWidth;
	uvm.R = (cr.x + cr.width) / textureWidth;
	uvm.T = cr.y / textureHeight;
	uvm.B = (cr.y + cr.height) / textureHeight;
	return uvm;
}

void GetFontVertexBuffer(Font* font, char c, SimpleVertexCombined* scv) {
	Rect tw1 = getFontMeshRect(font, c);
	Rect uvm1 = getFontUV(font, c);

	scv[0] = (SimpleVertexCombined){ {tw1.L,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.L, uvm1.T} };
	scv[1] = (SimpleVertexCombined){ {tw1.R,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.R, uvm1.T} };
	scv[2] = (SimpleVertexCombined){ {tw1.R,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.R, uvm1.T} };
	scv[3] = (SimpleVertexCombined){ {tw1.R,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm1.R, uvm1.T} };
}