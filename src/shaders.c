#include "shaders.h"

#include "log.h"
#include "file.h"
#include <stdio.h>
#include <string.h>
#include "GL/gl3w.h"

static uint createShader(char* src, uint type)
{
    uint shader = glCreateShader(type);
    if (shader == 0) {
        print_error("Failed to create shader");
        return 0;
    }

    glShaderSource(shader, 1, (const char* const*)&src, NULL);
    free(src);
    glCompileShader(shader);

    int status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        char info[infoLen];
        int len;
        glGetShaderInfoLog(shader, infoLen, &len, info);
        print_error("Failed to compile shader: %s", info);
    }

    return shader;
}

static uint createProgram(Shader_t* shaderList, size_t n)
{
    uint program = glCreateProgram();
    for (size_t i = 0; i < n; ++i) {
        glAttachShader(program, shaderList[i].name);
    }
    glLinkProgram(program);
    return program;
}

Shader_t newShader(char* path, uint type)
{
    char* src = loadFile(path);
    if (src == NULL) {
        print_error("failed to load file: %s", path);
        return (Shader_t) { 0 };
    }

    Shader_t shader = {
        .name = createShader(src, type),
        .type = type,
        .path = path
    };

    return shader;
}

Program_t newProgram(Shader_t* shaderList, size_t n)
{
    Program_t program = {
        .name = createProgram(shaderList, n),
        .shaderList = shaderList
    };
    return program;
}
