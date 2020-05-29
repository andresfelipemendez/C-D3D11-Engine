#pragma once

#define DllExport __declspec(dllexport)

#define PI (3.14159265358979323846)

typedef struct
{
    float X, Y, Z;
    float color[4];
} VERTEX;

typedef struct {
    float x, y ,z;
} vector3;

typedef struct {
    float Pos[3];
    float Col[3];
} SimpleVertexCombined;


DllExport vector3 add(vector3 a, vector3 b);

#define SET_CLEAR_COLOR(name) void name(float *color)
typedef SET_CLEAR_COLOR(set_clear_color);

#define SET_WORLD_VIEW_PROJECTION_MATRIX(name) void name(vector3 up, vector3 position, vector3 lookAt, vector3 rot)
typedef SET_WORLD_VIEW_PROJECTION_MATRIX(set_world_view_projection_matrix);

#define SET_VERTEX_BUFFER(name) void name(unsigned int *stride, unsigned int *offset)
typedef SET_VERTEX_BUFFER(set_vertex_buffer);

#define pVoid_pUIntUint(name) void* name(unsigned int *stride, unsigned int size)

typedef pVoid_pUIntUint(create_index_buffer);

#define DRAW(name) void name(void)
typedef DRAW(draw);

#define DEBUG_PLATFORM_PRINT_CONSOLE(name) void name(char *message)
typedef DEBUG_PLATFORM_PRINT_CONSOLE(debug_platform_print_console);

typedef struct {
    debug_platform_print_console *DEBUGPlatformPrintConsole;
    set_clear_color *SETClearColor;
    set_world_view_projection_matrix *SETWorldViewProjectionMatrix;
    set_vertex_buffer *SETVertexBuffer;
    create_index_buffer *CreateIndexBuffer;
    draw *Draw;
} GameMemory;