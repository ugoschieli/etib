#include "GL/gl3w.h"
#include "map.h"
#include "uniform.h"
#include "mat4.h"
#include "shaders.h"
#include "file.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

char* ltrim(char* s)
{
    while (isspace(*s))
        s++;
    return s;
}

char* rtrim(char* s)
{
    char* back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char* trim(char* s)
{
    return rtrim(ltrim(s));
}

void pushCube(Map_t* map, Cube_t* cube)
{
    if (map->len + 1 < map->capacity) {
        memcpy(map->cubes + map->len, cube, sizeof(Cube_t));
        map->len += 1;
        return;
    }

    size_t newCap = map->capacity * 2;
    map->cubes = realloc(map->cubes, newCap);
    memcpy(map->cubes + map->len, cube, sizeof(Cube_t));
    map->len += 1;
    map->capacity = newCap;
}

void parseMap(char* mapData, GameState_t* state)
{
    char* line = strtok(mapData, ";");
    while (line != NULL && strcmp(line, "\n") != 0) {
        char* trimmed = trim(line);

        float x = atof(trim(strtok_r(trimmed, ",", &trimmed)));
        float y = atof(trim(strtok_r(NULL, ",", &trimmed)));
        float z = atof(trim(strtok_r(NULL, ",", &trimmed)));
        float r = atof(trim(strtok_r(NULL, ",", &trimmed)));
        float g = atof(trim(strtok_r(NULL, ",", &trimmed)));
        float b = atof(trim(strtok_r(NULL, ",", &trimmed)));

        /*printf("x: %f, y: %f, z: %f, r: %f, g: %f, b: %f\n", x, y, z, r, g, b);*/
        Cube_t cube = {
            { x, y, z },
            { r, g, b }
        };
        pushCube(&state->map, &cube);

        line = strtok(NULL, ";");
    }
}

void readMap(char* mapPath, GameState_t* state)
{
    char* mapData = loadFile(mapPath);
    parseMap(mapData, state);
}

void initMap(GameState_t* state)
{
    Vertex_t vertices[] = {
        (Vertex_t) { -0.5, -0.5, -0.5 }, // left bottom front 0
        (Vertex_t) { 0.5, -0.5, -0.5 }, // right bottom front 1
        (Vertex_t) { -0.5, -0.5, 0.5 }, // left up front      2
        (Vertex_t) { 0.5, -0.5, 0.5 }, // right up front      3

        (Vertex_t) { -0.5, 0.5, -0.5 }, // left bottom back 4
        (Vertex_t) { 0.5, 0.5, -0.5 }, // right bottom back 5
        (Vertex_t) { -0.5, 0.5, 0.5 }, // left up back      6
        (Vertex_t) { 0.5, 0.5, 0.5 }, // right up back      7
    };

    GLuint indices[] = {
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

    GLfloat colors[] = {
        1, 0, 0, 1, 0, 0, //
        0, 1, 0, 0, 1, 0, //
        0, 0, 1, 0, 0, 1, //
        1, 0, 1, 1, 0, 1, //
        1, 1, 0, 1, 1, 0, //
        0, 1, 1, 0, 1, 1, //
    };

    state->map.cubes = malloc(9 * sizeof(Cube_t));
    state->map.len = 0;
    state->map.capacity = 9;
    readMap("./map", state);

    glCreateVertexArrays(1, &(state->map.vao));
    glCreateBuffers(1, &(state->map.vbo));
    glCreateBuffers(1, &(state->map.ebo));

    glNamedBufferStorage(state->map.vbo, 8 * sizeof(Vertex_t), vertices, 0);
    glNamedBufferStorage(state->map.ebo, 36 * sizeof(GLuint), indices, 0);

    glVertexArrayVertexBuffer(state->map.vao, 0, state->map.vbo, 0, sizeof(Vertex_t));
    glVertexArrayElementBuffer(state->map.vao, state->map.ebo);

    Shader_t shaderList[] = {
        newShader("shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);

    state->map.program = program;

    glEnableVertexArrayAttrib(state->map.vao, 0);
    glVertexArrayAttribFormat(state->map.vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(state->map.vao, 0, 0);

    mat4 base = { (vec4) { 1, 0, 0, 0 }, (vec4) { 0, 0, -1, 0 }, (vec4) { 0, 1, 0, 0 }, (vec4) { 0, 0, 0, 1 } };
    mat4 center = translationMat4((vec4) { ((float)state->numUnitWidth / 2), 0, (float)state->numUnitHeight / 2, 0 });
    base = multiplyMat4(&base, &center);
    mat4 proj = orthoMat4(0, state->numUnitWidth, 0, state->numUnitHeight, 0, 100);

    setUniformMat4(state->map.program.name, "base", &base);
    setUniformMat4(state->map.program.name, "proj", &proj);

    setUniform3fv(state->map.program.name, "colors", colors, 12);
}

void renderMap(GameState_t* state)
{
    for (size_t i = 0; i < state->map.len; i++) {
        Cube_t cube = state->map.cubes[i];
        mat4 tr = translationMat4((vec4) { cube.pos.x, cube.pos.y, cube.pos.z, 0 });
        setUniformMat4(state->map.program.name, "tr", &tr);
    }

    glUseProgram(state->map.program.name);
    glBindVertexArray(state->map.vao);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, state->map.len);
}
