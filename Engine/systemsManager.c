#include "systemsManager.h"
#include "RenderingComponent.h"

void initSystemManager() {
	/**numRenderingComponents = (unsigned int*) malloc(sizeof(unsigned int));
	**numRenderingComponents = 1;*/

	numSystems = 0;
}

void registerSystem(void* system)
{
	if (numSystems >= 512)
	{
		// todo fail or resize?
	}

	systems[numSystems] = system;
	numSystems++;
}

void runSystems() {
	for (int i = 0; i < numSystems; i++)
	{
		systems[i]();
	}
}
