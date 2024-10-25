#include <stdarg.h>
#include <stdio.h>
#include "GL/gl3w.h"

static void flog(const char* prefix, const char* format, va_list args)
{
    fprintf(stderr, "%s ", prefix);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}

void print_debug(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    flog("[DEBUG]", format, ap);
}

void print_error(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    flog("[ERROR]", format, ap);
}

void logGlError(const char* msg)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        print_error("%s", msg);
        if (error == GL_INVALID_VALUE)
            print_error("invalid value");
        else if (error == GL_INVALID_OPERATION)
            print_error("invalid operation");
        else if (error == GL_INVALID_ENUM)
            print_error("invalid enum");
        else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
            print_error("invalid fb ops");
        else if (error == GL_OUT_OF_MEMORY)
            print_error("out of vram :(");
        else if (error == GL_STACK_UNDERFLOW)
            print_error("stack underflow");
        else if (error == GL_STACK_OVERFLOW)
            print_error("stack overflow");
    }
}
