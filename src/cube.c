#include "cube.h"

Vertex_t vertices_g[] = {
    (Vertex_t) { -0.5, -0.5, -0.5 }, // left bottom front 0
    (Vertex_t) { 0.5, -0.5, -0.5 }, // right bottom front 1
    (Vertex_t) { -0.5, -0.5, 0.5 }, // left up front      2
    (Vertex_t) { 0.5, -0.5, 0.5 }, // right up front      3

    (Vertex_t) { -0.5, 0.5, -0.5 }, // left bottom back 4
    (Vertex_t) { 0.5, 0.5, -0.5 }, // right bottom back 5
    (Vertex_t) { -0.5, 0.5, 0.5 }, // left up back      6
    (Vertex_t) { 0.5, 0.5, 0.5 }, // right up back      7
};

GLuint indices_g[] = {
    0, 1, 3, // first triangle front face
    3, 2, 0, // second triangle front face

    0, 2, 6, // first triangle left face
    6, 4, 0, // second triangle left face

    1, 3, 7, // first triangle right face
    7, 5, 1, // second triangle right face

    4, 5, 7, // first triangle back face
    7, 6, 4, // second triangle back face

    2, 3, 7, // first triangle up face
    7, 6, 2, // second triangle up face

    0, 1, 5, // first triangle bottom face
    5, 4, 0, // second triangle bottom face
};

void initGlobalState(CubeGlobal_t* state)
{
    glCreateBuffers(1, &(state->vbo));
    glCreateBuffers(1, &(state->ebo));
    glNamedBufferStorage(state->vbo, 8 * sizeof(Vertex_t), vertices_g, 0);
    glNamedBufferStorage(state->ebo, 36 * sizeof(GLuint), indices_g, 0);
}

Cube_t newCube(const CubeGlobal_t* state, const Program_t* program, AttribInit init)
{
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, state->vbo, 0, sizeof(Vertex_t));
    glVertexArrayElementBuffer(vao, state->ebo);

    Cube_t cube = {
        .vao = vao,
        .program = program,
        .x = 0,
        .y = 0,
        .z = 0,
    };

    init(&cube);

    return cube;
}

void renderCube(const Cube_t* cube)
{
    glUseProgram(cube->program->name);
    glBindVertexArray(cube->vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
