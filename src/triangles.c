#include "triangles.h"

#include "GL/gl3w.h"

Triangle_t newTriangle(const float* vertices, size_t n, uint* indices, const Program_t* program, AttribInit init)
{
    uint vao;
    uint vbo;
    uint ebo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ebo);
    glNamedBufferStorage(vbo, (GLsizeiptr)(n * sizeof(float)), vertices, 0);
    glNamedBufferStorage(ebo, (GLsizeiptr)(3 * sizeof(uint)), indices, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6 * sizeof(float));
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
