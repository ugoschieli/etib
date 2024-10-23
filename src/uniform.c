#include "uniform.h"
#include <stdbool.h>

void setUniformMat4(GLuint program, char* name, mat4* mat)
{
    glUseProgram(program);
    GLint uniformLoc = glGetUniformLocation(program, name);
    glUniformMatrix4fv(uniformLoc, 1, false, (GLfloat*)mat);
}
