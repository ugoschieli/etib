#ifndef UNIFORM_H
#define UNIFORM_H

#include "mat4.h"

void setUniformMat4(uint program, char* name, mat4* mat);

void setUniformMat4v(uint program, char* name, mat4* mat, size_t n);

void setUniform3fv(uint program, char* name, float* data, size_t n);

void setUniform4fv(uint program, char* name, float* data, size_t n);

#endif // UNIFORM_H
