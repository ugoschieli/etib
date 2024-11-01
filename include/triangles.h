#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "shaders.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct Triangle {
    uint vao;
    uint vbo;
    const Program_t* program;
    const float* vertices;
    const uint* indices;
} Triangle_t;

typedef void (*AttribInit)(uint);

Triangle_t newTriangle(const float* vertices, size_t n, uint* indices, const Program_t* program, AttribInit init);

void renderTriangle(const Triangle_t* triangle);

#endif // TRIANGLES_H
