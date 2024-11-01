#ifndef CUBE_H
#define CUBE_H

#include "shaders.h"

typedef struct CubeGlobal {
    uint vbo;
    uint ebo;
} CubeGlobal_t;

typedef struct Vertex {
    float x;
    float y;
    float z;
} Vertex_t;

typedef struct Cube {
    uint vao;
    const Program_t* program;
    float x;
    float y;
    float z;
} Cube_t;

typedef void (*AttribInit)(Cube_t*);

void initGlobalState(CubeGlobal_t* state);

Cube_t newCube(const CubeGlobal_t* state, const Program_t* program, AttribInit init);

void renderCube(const Cube_t* cube);

#endif // CUBE_H
