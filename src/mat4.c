#include "mat4.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

GLfloat indexMat4(mat4* mat, size_t m, size_t n)
{
    assert(n >= 1 && n <= 4);
    switch (n) {
    case 1:
        return indexVec4(&mat->v1, m);
    case 2:
        return indexVec4(&mat->v2, m);
    case 3:
        return indexVec4(&mat->v3, m);
    case 4:
        return indexVec4(&mat->v4, m);
    default:
        return 0;
    };
}

void setColFromVec4(mat4* mat, vec4 vec, size_t n)
{
    assert(n >= 1 && n <= 4);
    switch (n) {
    case 1:
        mat->v1 = vec;
        break;
    case 2:
        mat->v2 = vec;
        break;
    case 3:
        mat->v3 = vec;
        break;
    case 4:
        mat->v4 = vec;
        break;
    };
}

mat4 initMat4(vec4 col1, vec4 col2, vec4 col3, vec4 col4)
{
    mat4 mat = { 0 };
    setColFromVec4(&mat, col1, 1);
    setColFromVec4(&mat, col2, 2);
    setColFromVec4(&mat, col3, 3);
    setColFromVec4(&mat, col4, 4);
    return mat;
}

void setValMat4(mat4* mat, GLfloat val, size_t m, size_t n)
{
    assert(n >= 1 && n <= 4);
    switch (n) {
    case 1:
        setValVec4(&mat->v1, val, m);
        break;
    case 2:
        setValVec4(&mat->v2, val, m);
        break;
    case 3:
        setValVec4(&mat->v3, val, m);
        break;
    case 4:
        setValVec4(&mat->v4, val, m);
        break;
    };
}

/*GLfloat indexMat4(mat4* mat, size_t m, size_t n)*/
/*{*/
/*    return mat->matrix[4 * m + n];*/
/*}*/

/*void setValMat4(mat4* mat, GLfloat val, size_t m, size_t n)*/
/*{*/
/*    mat->matrix[4 * m + n] = val;*/
/*}*/

mat4 identityMat4(void)
{
    mat4 i4 = { 0 };
    for (int i = 1; i <= 4; ++i) {
        setValMat4(&i4, 1.0, i, i);
    }
    return i4;
}

mat4 transposedMat4(mat4* mat)
{
    mat4 t = { 0 };
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            setValMat4(&t, indexMat4(mat, j, i), i, j);
        }
    }
    return t;
}

mat4 multiplyMat4(mat4* m1, mat4* m2)
{
    mat4 r = { 0 };
    for (size_t i = 1; i <= 4; ++i) {
        for (size_t j = 1; j <= 4; ++j) {
            GLfloat sum = 0;
            for (size_t k = 1; k <= 4; ++k) {
                sum += indexMat4(m1, i, k) * indexMat4(m2, k, j);
            }
            setValMat4(&r, sum, i, j);
        }
    }
    return r;
}

mat4 scalingMat4(vec4 u)
{
    mat4 s = { 0 };
    setColFromVec4(&s, (vec4) { u.x, 0, 0, 0 }, 1);
    setColFromVec4(&s, (vec4) { 0, u.y, 0, 0 }, 2);
    setColFromVec4(&s, (vec4) { 0, 0, u.z, 0 }, 3);
    setColFromVec4(&s, (vec4) { 0, 0, 0, 1 }, 4);
    return s;
}

mat4 translationMat4(vec4 u)
{
    mat4 tr = { 0 };
    setColFromVec4(&tr, (vec4) { 1, 0, 0, 0 }, 1);
    setColFromVec4(&tr, (vec4) { 0, 1, 0, 0 }, 2);
    setColFromVec4(&tr, (vec4) { 0, 0, 1, 0 }, 3);
    setColFromVec4(&tr, (vec4) { u.x, u.y, u.z, 1 }, 4);
    return tr;
}

mat4 rotationMat4(vec4 u, GLfloat a)
{
    mat4 rot = { 0 };

    vec4 col1 = {
        u.x * u.x * (1 - cosf(a)) + cosf(a),
        u.x * u.y * (1 - cosf(a)) + u.z * sinf(a),
        u.x * u.z * (1 - cosf(a)) - u.y * sinf(a),
        0
    };

    vec4 col2 = {
        u.x * u.y * (1 - cosf(a)) - u.z * sinf(a),
        u.y * u.y * (1 - cosf(a)) + cosf(a),
        u.y * u.z * (1 - cosf(a)) + u.x * sinf(a),
        0
    };

    vec4 col3 = {
        u.x * u.z * (1 - cosf(a)) + u.y * sinf(a),
        u.y * u.z * (1 - cosf(a)) - u.x * sinf(a),
        u.z * u.z * (1 - cosf(a)) + cosf(a),
        0
    };

    vec4 col4 = { 0, 0, 0, 1.0 };

    setColFromVec4(&rot, col1, 1);
    setColFromVec4(&rot, col2, 2);
    setColFromVec4(&rot, col3, 3);
    setColFromVec4(&rot, col4, 4);

    return rot;
}

mat4 orthoMat4(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
    return initMat4(
        (vec4) { 2 / (right - left), 0, 0, 0 },
        (vec4) { 0, 2 / (top - bottom), 0, 0 },
        (vec4) { 0, 0, -2 / (far - near), 0 },
        (vec4) { -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1 });
}

void toArrayMat4(mat4* mat, GLfloat* buf)
{
    memcpy(buf, mat, 16 * sizeof(GLfloat));
}

void printMat4(mat4* mat)
{
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            printf("%f ", indexMat4(mat, i, j));
        }
        printf("\n");
    }
    printf("\n");
}
