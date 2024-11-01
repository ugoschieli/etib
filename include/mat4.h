#ifndef MAT4_H
#define MAT4_H

#include <stdlib.h>
#include "vec4.h"

typedef struct mat4 {
    vec4 v1;
    vec4 v2;
    vec4 v3;
    vec4 v4;
} mat4;

/*typedef struct mat4 {*/
/*    GLfloat matrix[4 * 4];*/
/*} mat4;*/

float indexMat4(mat4* mat, size_t m, size_t n);

void setValMat4(mat4* mat, float val, size_t m, size_t n);

mat4 initMat4(vec4 col1, vec4 col2, vec4 col3, vec4 col4);

void setColFromVec4(mat4* mat, vec4 vec, size_t n);

mat4 identityMat4(void);

mat4 transposedMat4(mat4* mat);

mat4 multiplyMat4(mat4* m1, mat4* m2);

mat4 scalingMat4(vec4 u);

mat4 translationMat4(vec4 u);

mat4 rotationMat4(vec4 u, float a);

mat4 orthoMat4(float left, float right, float bottom, float top, float near, float far);

void toArrayMat4(mat4* mat, float* buf);

void printMat4(mat4* mat);

#endif // MAT4_H
