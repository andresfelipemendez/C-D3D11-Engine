#pragma once
#include "RenderingComponent.h"

//#include <cstddef>

#define DllExport __declspec(dllexport)
#define PI (3.14159265358979323846)

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
typedef unsigned int size_t;

typedef struct {
    float x, y ,z;
} vector3;


DllExport vector3 add(vector3 a, vector3 b);

#define pVoid_pUIntUint(name) void* name(unsigned int *stride, unsigned int size)
typedef pVoid_pUIntUint(create_index_buffer);

#define void_pChar(name) void name(char *message)
typedef void_pChar(print);

void *ptr;
typedef void (*void_f)(char*);
static print *pPrint;

void *pCreateIndexBuffer;
typedef void (*CreateIndexBuffer_f)(unsigned int*, unsigned int);
#define createIndexBuffer ((CreateIndexBuffer_f) pCreateIndexBuffer)

typedef struct {
    create_index_buffer *CreateIndexBuffer;
    print *Print;
} GameMemory;

#define void_pGameMemory(name) DllExport void name(GameMemory* memory)
typedef void_pGameMemory(start);
typedef void_pGameMemory(update);

void Print(char* text);