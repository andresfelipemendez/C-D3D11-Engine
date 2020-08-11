#pragma once
#include "Components/RenderingComponent.h"
#include "Components/InputComponent.h"

#define DllExport __declspec(dllexport)
#define PI (3.14159265358979323846)

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct {
    float x, y ,z;
} vector3;

DllExport vector3 add(vector3 a, vector3 b);

#define pVoid_pUIntUint(name) void* name(unsigned int *indices, unsigned int size)
typedef pVoid_pUIntUint(create_index_buffer);

#define pVoid_pVertexUint(name) void* name(SimpleVertexCombined* vertexBuffer, unsigned int size)
typedef pVoid_pVertexUint(create_vertex_buffer);



void* pUpdateVertexBuffer;
typedef void* (*UpdateVertexBuffer_f)(unsigned int*, unsigned int);
#define updateVertexBuffer ((UpdateVertexBuffer_f) pUpdateVertexBuffer)

#define pVoid_pVertexVertexUint(name) void* name(void* pVertexBuffer, SimpleVertexCombined* newVertexBuffer, unsigned int size)
typedef pVoid_pVertexVertexUint(update_vertex_buffer);

#define pVoid_pVoidpVoid(name) void* name(unsigned int numIndices,void *indexBuffer, void* vertexBuffer)
typedef pVoid_pVoidpVoid(set_buffers);

#define InputComponent_Void(name) InputComponent name()
typedef InputComponent_Void(get_input);

#define void_pChar(name) void name(char *message)
typedef void_pChar(print);

void *ptr;
typedef void (*void_f)(char*);
#define PRINT ((void_f) ptr)

void* pCreateIndexBuffer;
typedef void* (*CreateIndexBuffer_f)(unsigned int*, unsigned int);
#define createIndexBuffer ((CreateIndexBuffer_f) pCreateIndexBuffer)

void* pCreateVertexBuffer;
typedef void* (*CreateVertexBuffer_f)(SimpleVertexCombined*, unsigned int);
#define createVertexBuffer ((CreateVertexBuffer_f) pCreateVertexBuffer)

void* pSetBuffers;
typedef void* (*SetBuffers_f)(vector3,unsigned int,void*,void* );
#define setBuffers ((SetBuffers_f) pSetBuffers)

void* pGetInput;
typedef InputComponent (*pGetInput_f)();
#define GetInput ((pGetInput_f) pGetInput)

typedef struct {
        void* memory;
        create_index_buffer *CreateIndexBuffer;
        create_vertex_buffer *CreateVertexBuffer;
        update_vertex_buffer* UpdateVertexBuffer;
        set_buffers *SetBuffers;
        get_input* getInput;
        print *Print;
} GameMemory;

           /*__declspec(dllexport)
extern "C" __declspec(dllexport) void __cdecl*/

#define void_pGameMemory(name) DllExport void name(GameMemory* memory)
typedef void_pGameMemory(pGameMemory);

void_pGameMemory(Start);
void_pGameMemory(SetMethodPointers);
void_pGameMemory(Update);

//typedef void_pGameMemory(set_method_pointers);
//typedef void_pGameMemory(update);
