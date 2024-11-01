#ifndef VEC4_H
#define VEC4_H

#include <stdlib.h>

typedef struct vec4 {
    float x;
    float y;
    float z;
    float w;
} vec4;

float indexVec4(vec4* vec, size_t n);

void setValVec4(vec4* vec, float val, size_t n);

float normVec4(vec4* vec);

void normalizeVec4(vec4* vec);

#endif // VEC4_H
