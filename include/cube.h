#ifndef CUBE_H
#define CUBE_H

#include <GL/gl3w.h>
#include "shaders.h"

typedef struct CubeGlobal {
    GLuint vbo;
    GLuint ebo;
} CubeGlobal_t;

typedef struct Vertex {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vertex_t;

typedef struct Cube {
    GLuint vao;
    const Program_t* program;
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Cube_t;

typedef void (*AttribInit)(Cube_t*);

void initGlobalState(CubeGlobal_t* state);

Cube_t newCube(const CubeGlobal_t* state, const Program_t* program, AttribInit init);

void renderCube(const Cube_t* cube);

#endif // CUBE_H
