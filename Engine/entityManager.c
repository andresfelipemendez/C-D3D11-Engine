#include "entityManager.h"

static void* entities[512];
static unsigned int numEntities = 0;
unsigned int* pNumEntities = &numEntities;

void InitEntityManager() {
	archetypeRendererTraslationInput = malloc(sizeof(void*));
	archetypeRendererTraslationInput->entityId = malloc(sizeof(int) * 512);
	archetypeRendererTraslationInput->renderingComponents = malloc(sizeof(RenderingComponent) * 512);
	archetypeRendererTraslationInput->traslationComponents = malloc(sizeof(TraslationComponent) * 512);
	archetypeRendererTraslationInput->inputComponents = malloc(sizeof(InputComponent) * 512);
}


void* createEntityArchetiypeRendererTraslationInput()
{

	if(numEntities >= 512) {
		// todo fail or expand
		return 0;
	}

	return entities[numEntities++];
}
