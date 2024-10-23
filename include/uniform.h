#ifndef UNIFORM_H
#define UNIFORM_H

#include <GL/gl3w.h>
#include "mat4.h"

void setUniformMat4(GLuint program, char* name, mat4* mat);

#endif // UNIFORM_H
