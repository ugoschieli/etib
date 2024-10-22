#include "shaders.h"
#include "log.h"
#include <stdio.h>
#include <string.h>

static char* loadFile(char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size == -1) {
        return NULL;
    }

    rewind(f);
    char* buf = calloc(sizeof(char), (size_t)(size + 1));
    if (buf == NULL) {
        return NULL;
    }

    size_t n = fread(buf, sizeof(char), (size_t)size, f);
    if (n == 0) {
        print_error("failed to read file: %s", path);
    }
    fclose(f);

    return buf;
}

static GLuint createShader(char* src, GLenum type)
{
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        print_error("Failed to create shader");
        return 0;
    }

    glShaderSource(shader, 1, (const GLchar* const*)&src, NULL);
    free((void*)src);
    glCompileShader(shader);

    GLint status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        GLchar info[infoLen];
        GLsizei len;
        glGetShaderInfoLog(shader, infoLen, &len, info);
        print_error("Failed to compile shader: %s", info);
    }

    return shader;
}

static GLuint createProgram(Shader_t* shaderList, size_t n)
{
    GLuint program = glCreateProgram();
    for (size_t i = 0; i < n; ++i) {
        glAttachShader(program, shaderList[i].name);
    }
    glLinkProgram(program);
    return program;
}

Shader_t newShader(char* path, GLenum type)
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
