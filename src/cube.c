#include "cube.h"

Cube_t newCube(const Vertex_t* vertices, GLsizeiptr size, GLuint* indices, const Program_t* program, AttribInit init)
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ebo);
    glNamedBufferStorage(vbo, size, vertices, 0);
    glNamedBufferStorage(ebo, 36 * sizeof(GLuint), indices, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex_t));
    glVertexArrayElementBuffer(vao, ebo);

    init(vao);

    Cube_t cube = {
        .vao = vao,
        .vbo = vbo,
        .program = program,
        .vertices = vertices,
        .indices = indices
    };
    return cube;
}

void renderCube(const Cube_t* cube)
{
    glUseProgram(cube->program->name);
    glBindVertexArray(cube->vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
