#ifndef SHADERS_H
#define SHADERS_H

#include <stdlib.h>

typedef struct Shader {
    uint name;
    uint type;
    const char* path;
} Shader_t;

typedef struct Program {
    Shader_t* shaderList;
    uint name;
    int padding;
} Program_t;

Shader_t newShader(char* path, uint type);
Program_t newProgram(Shader_t* shaderList, size_t n);

#endif // SHADERS_H
