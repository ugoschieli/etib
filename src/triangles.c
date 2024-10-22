#include "triangles.h"
#include "log.h"
#include <stdio.h>

Triangle_t newTriangle(GLfloat* vertices, size_t n, Program_t* program)
{
    GLuint vao;
    GLuint vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, n * sizeof(GLfloat), vertices, 0);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glUseProgram(program->name);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    Triangle_t tri = {
        .vao = vao,
        .vbo = vbo,
        .program = program,
        .vertices = vertices,
    };
    return tri;
}

void renderTriangle(Triangle_t* triangle)
{
    glBindVertexArray(triangle->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    logGlError("draw triangle");
}
