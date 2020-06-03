#pragma once

typedef void (*void_p)(void);

static void_p systems[512];
unsigned int numSystems = 0;

void InitSystemManager();
void registerSystem(void* system);

