#ifndef UNIFORM_H
#define UNIFORM_H

#include <GL/gl3w.h>
#include "mat4.h"

void setUniformMat4(GLuint program, char* name, mat4* mat);

void setUniform3fv(GLuint program, char* name, GLfloat* data, size_t n);

#endif // UNIFORM_H
