#include "uniform.h"

#include <stdbool.h>
#include "GL/gl3w.h"

void setUniformMat4(uint program, char* name, mat4* mat)
{
    int uniformLoc = glGetUniformLocation(program, name);
    glProgramUniformMatrix4fv(program, uniformLoc, 1, false, (float*)mat);
}

void setUniform3fv(uint program, char* name, float* data, size_t n)
{
    int uniformLoc = glGetUniformLocation(program, name);
    glProgramUniform3fv(program, uniformLoc, n, data);
}
