#pragma once

#include "Components/RenderingComponent.h"
#include "Components/RectangleComponent.h"
#include "Components/TraslationComponent.h"
#include "Components/InputComponent.h"
#include "Components/BounceComponent.h"

typedef struct {
	RenderingComponent* renderingComponents;
	RectangleComponent* rectangles;
	TraslationComponent* translations;
	InputComponent* inputComponents;
} ArchetypeRendererTraslationInput;

ArchetypeRendererTraslationInput* archetypeRendererTraslationInput;

typedef struct {
	RenderingComponent* renderingComponents;
	TraslationComponent* translations;
	BounceComponent* bounceComponents;
} ArchetypeRendererTraslationBounce;

ArchetypeRendererTraslationBounce* archetypeRendererTraslationBounce;
