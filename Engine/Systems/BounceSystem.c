#include "BounceSystem.h"
#include "../EntityManager.h"

extern unsigned int* pNumEntitiesARRTB;

void BounceSystem(void) {
        TraslationComponent* t = archetypeRendererTraslationBounce->translations;
        BounceComponent* b = archetypeRendererTraslationBounce->bounceComponents;

        for (int i = 0; i < *pNumEntitiesARRTB; ++i)
        {
                if (t->y >= 1.75) {
                        b->velocity.y = -b->velocity.y;
                }
                if (t->x >= 2.75) {
                        b->velocity.x = -b->velocity.x;
                }
                if (t->y <= -2.05) {
                        b->velocity.y = -b->velocity.y;
                }
                if (t->x <= -2.65) {
                        b->velocity.x = -b->velocity.x;
                }

        	t->x += b->velocity.x;
        	t->y += b->velocity.y;
        }
}