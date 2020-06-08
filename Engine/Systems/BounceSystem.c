#include "BounceSystem.h"
#include "../EntityManager.h"

extern unsigned int* pNumEntitiesARRTB;

void WoldBounce(TraslationComponent* t, BounceComponent* b) {
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
}

void PaddleBounce(TraslationComponent* t, TraslationComponent* t1, BounceComponent* b) {
        float wd = 0.1; 
        float bh = 0.1;
        float ph = 1.0;
        
        if (((t->y + bh  >= t1->y - ph) && (t->y - bh <= t1->y + ph)) &&
            ((t->x + wd  >= t1->x - wd) && (t->x - wd <= t1->x + wd))) {

                float hor = (t->x + wd) - (t1->x - wd);
                float hol = (t1->x + wd) - (t->x - wd);

                float vot = (t->y + bh) - (t1->y - ph);
                float vob = (t1->y + ph) - (t->y - bh);

                float horizontalOverlap = hor < hol ? hor : hol;
                float verticalOverlap = vob < vot ? vob : vot;

                if (horizontalOverlap > verticalOverlap) {
                        b->velocity.y = -b->velocity.y;
                }
                else {
                        b->velocity.x = -b->velocity.x;
                }
        }
}
 
void BounceSystem(void) {
        TraslationComponent* t = archetypeRendererTraslationBounce->translations;
        BounceComponent* b = archetypeRendererTraslationBounce->bounceComponents;
       
        TraslationComponent t1 = archetypeRendererTraslationInput->translations[0];
        TraslationComponent t2 = archetypeRendererTraslationInput->translations[1];


        WoldBounce(t, b);
        PaddleBounce(t, &t1, b);
        PaddleBounce(t, &t2, b);


        t->x += b->velocity.x;
        t->y += b->velocity.y;

}