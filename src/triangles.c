#include "triangles.h"

Triangle_t newTriangle(const GLfloat* vertices, size_t n, GLuint* indices, const Program_t* program, AttribInit init)
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ebo);
    glNamedBufferStorage(vbo, (GLsizeiptr)(n * sizeof(GLfloat)), vertices, 0);
    glNamedBufferStorage(ebo, (GLsizeiptr)(3 * sizeof(GLuint)), indices, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6 * sizeof(GLfloat));
    glVertexArrayElementBuffer(vao, ebo);

    init(vao);

    Triangle_t tri = {
        .vao = vao,
        .vbo = vbo,
        .program = program,
        .vertices = vertices,
        .indices = indices
    };
    return tri;
}

void renderTriangle(const Triangle_t* triangle)
{
    glUseProgram(triangle->program->name);
    glBindVertexArray(triangle->vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}
