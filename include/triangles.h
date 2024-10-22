#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <GL/gl3w.h>
#include "shaders.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct Triangle {
    GLuint vao;
    GLuint vbo;
    Program_t* program;
    GLfloat* vertices;
} Triangle_t;

Triangle_t newTriangle(GLfloat* vertices, size_t n, Program_t* program);

void renderTriangle(Triangle_t* triangle);

#endif // TRIANGLES_H
