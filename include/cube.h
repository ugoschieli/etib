#ifndef CUBE_H
#define CUBE_H

#include <GL/gl3w.h>
#include "shaders.h"

typedef struct Vertex {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vertex_t;

typedef struct Cube {
    GLuint vao;
    GLuint vbo;
    const Program_t* program;
    const Vertex_t* vertices;
    const GLuint* indices;
} Cube_t;

typedef void (*AttribInit)(GLuint);

Cube_t newCube(const Vertex_t* vertices, GLsizeiptr size, GLuint* indices, const Program_t* program, AttribInit init);

void renderCube(const Cube_t* cube);

#endif // CUBE_H
