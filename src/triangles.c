#include "triangles.h"

Triangle_t newTriangle(const GLfloat* vertices, size_t n, const Program_t* program, AttribInit init)
{
    GLuint vao;
    GLuint vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, (GLsizeiptr)(n * sizeof(GLfloat)), vertices, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6 * sizeof(GLfloat));

    init(vao);

    Triangle_t tri = {
        .vao = vao,
        .vbo = vbo,
        .program = program,
        .vertices = vertices,
    };
    return tri;
}

void renderTriangle(const Triangle_t* triangle)
{
    glUseProgram(triangle->program->name);
    glBindVertexArray(triangle->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
