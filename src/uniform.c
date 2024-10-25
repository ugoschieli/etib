#include "uniform.h"
#include <stdbool.h>

void setUniformMat4(GLuint program, char* name, mat4* mat)
{
    GLint uniformLoc = glGetUniformLocation(program, name);
    glProgramUniformMatrix4fv(program, uniformLoc, 1, false, (GLfloat*)mat);
}

void setUniform3fv(GLuint program, char* name, GLfloat* data, size_t n)
{
    GLint uniformLoc = glGetUniformLocation(program, name);
    glProgramUniform3fv(program, uniformLoc, n, data);
}
