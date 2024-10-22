#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <GL/gl3w.h>
#include "shaders.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct Triangle {
    GLuint vao;
    GLuint vbo;
    const Program_t* program;
    const GLfloat* vertices;
} Triangle_t;

typedef void (*AttribInit)(void);

Triangle_t newTriangle(const GLfloat* vertices, size_t n, const Program_t* program, AttribInit init);

void renderTriangle(const Triangle_t* triangle);

#endif // TRIANGLES_H
