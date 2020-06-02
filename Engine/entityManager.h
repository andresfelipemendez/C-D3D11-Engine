#pragma once

#include "RenderingComponent.h"
#include "TraslationComponent.h"
#include "InputComponent.h"

// SOA or AOS? this is a SOA but I'm not sure if it is what the DOD dictates
typedef struct {
	int* entityId;
	RenderingComponent* renderingComponents;
	TraslationComponent* traslationComponents;
	InputComponent* inputComponents;
} ArchetypeRendererTraslationInput;

ArchetypeRendererTraslationInput* archetypeRendererTraslationInput = 0;

void* createEntityArchetiypeRendererTraslationInput();

