#pragma once

#include "Components/RenderingComponent.h"
#include "Components/TraslationComponent.h"
#include "Components/InputComponent.h"

typedef struct {
	RenderingComponent* renderingComponents;
	TraslationComponent* translations;
	InputComponent* inputComponents;
} ArchetypeRendererTraslationInput;

ArchetypeRendererTraslationInput* archetypeRendererTraslationInput;

typedef struct {
	RenderingComponent* renderingComponents;
	TraslationComponent* translations;
	//BounceComponent* bounceComponents;
} ArchetypeRendererTraslationBounce;

ArchetypeRendererTraslationInput* archetypeRendererTraslationInput;
