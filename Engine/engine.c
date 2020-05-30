#include "engine.h"

vector3 add(vector3 a, vector3 b)
{
    vector3 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

void_pGameMemory(Start) {

    Print = memory->Print;
    Print("hi");

   /* renderComponents = malloc(sizeof(RenderComponent)* 512);
    numRenderComponents = 0;*/

    //Add Entity
    unsigned int indices[] = {0, 1, 2};
    void* iv = memory->CreateIndexBuffer(indices, 3);
    //renderComponents[numRenderComponents].indices = iv;
    

    SimpleVertexCombined verticesCombo[3] = {
        {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.5f}},
        {{0.5f, -0.5f, 0.0f}, {0.5f, 0.0f, 0.5f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.5f}}
    };
    
    //registerSystem(&renderSystem);
}