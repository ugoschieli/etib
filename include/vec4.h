#ifndef VEC4_H
#define VEC4_H

#include <stdlib.h>
#include <GL/glcorearb.h>

typedef struct vec4 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} vec4;

GLfloat indexVec4(vec4* vec, size_t n);

void setValVec4(vec4* vec, GLfloat val, size_t n);

GLfloat normVec4(vec4* vec);

void normalizeVec4(vec4* vec);

#endif // VEC4_H
