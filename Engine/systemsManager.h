#pragma once

typedef void (*void_p)(void);

static void_p systems[512];
unsigned int numSystems = 0;

void initSystemManager();
void registerSystem(void* system);

