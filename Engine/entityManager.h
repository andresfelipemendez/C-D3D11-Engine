#pragma once

#include "RenderingComponent.h"
#include "TraslationComponent.h"
#include "InputComponent.h"

typedef struct {
	RenderingComponent* renderingComponents;
	TraslationComponent* translations;
	InputComponent* inputComponents;
} ArchetypeRendererTraslationInput;

ArchetypeRendererTraslationInput* archetypeRendererTraslationInput;

//unsigned int createEntityArchetiypeRendererTraslationInput();

