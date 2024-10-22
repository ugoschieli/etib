#ifndef SHADERS_H
#define SHADERS_H

#include <GL/gl3w.h>
#include <stdlib.h>

typedef struct Shader {
    GLuint name;
    GLenum type;
    const char* path;
} Shader_t;

typedef struct Program {
    GLuint name;
    Shader_t* shaderList;
} Program_t;

Shader_t newShader(char* path, GLenum type);
Program_t newProgram(Shader_t* shaderList, size_t n);

#endif // SHADERS_H
