#include "BounceSystem.h"
#include "../EntityManager.h"
#include "RenderingSystem.h"
#include "../Engine.h"

extern unsigned int* pNumEntitiesARRTB;

void UpdateScore(unsigned int playerIndex) {
        int score = ++(archetypeFontRenderingComponentTraslationScoreComponent->scores[playerIndex]);
        void* vertexBuffer = archetypeFontRenderingComponentTraslationScoreComponent->fontRenderingComponets[playerIndex].pVertexBuffer;
        char charscore = score + '0';
        Rect tw2 = getFontMeshRect(&font_Arial, charscore);
        Rect uvm2 = getFontUV(&font_Arial, charscore);

        SimpleVertexCombined fvb2[] = {
                {{tw2.L,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.L, uvm2.T}},
                {{tw2.R,  0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.R, uvm2.T}},
                {{tw2.L, -0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.L, uvm2.B}},
                {{tw2.R, -0.1f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {uvm2.R, uvm2.B}},
        };

        TraslationComponent t3 = { 0 };
        t3.x = 0;
        t3.y = 0;
        t3.z = -5.15;
        archetypeRendererTraslationBounce->translations[0] = t3;

        updateVertexBuffer(vertexBuffer, fvb2, NELEMS(fvb2));
}

void WoldBounce(TraslationComponent* t, BounceComponent* b) {
        if (t->y >= 1.75) {
                b->velocity.y = -b->velocity.y;
        }
        if (t->x >= 2.75) {
                b->velocity.x = -b->velocity.x;
                UpdateScore(1);
        }
        if (t->y <= -2.05) {
                b->velocity.y = -b->velocity.y;
        }
        if (t->x <= -2.65) {
                b->velocity.x = -b->velocity.x;
                UpdateScore(0);
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