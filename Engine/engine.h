#pragma once
//#include <cstddef>

#define DllExport __declspec(dllexport)
#define PI (3.14159265358979323846)

typedef struct {
    float x, y ,z;
} vector3;

typedef struct {
    float Pos[3];
    float Col[3];
} SimpleVertexCombined;

DllExport vector3 add(vector3 a, vector3 b);

#define pVoid_pUIntUint(name) void* name(unsigned int *stride, unsigned int size)
typedef pVoid_pUIntUint(create_index_buffer);

#define void_pChar(name) void name(char *message)
typedef void_pChar(print);
print *Print;

typedef struct {
    create_index_buffer *CreateIndexBuffer;
    print *Print;
} GameMemory;

#define void_pGameMemory(name) DllExport void name(GameMemory* memory)
typedef void_pGameMemory(start);
typedef void_pGameMemory(update);