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
    mat4 mat = translationMat4((vec4) { cube->pos.x, cube->pos.y, cube->pos.z, 0 });
    vec4 colors = { cube->color.r, cube->color.g, cube->color.b, 1.0 };
    if (map->len + 1 < map->capacity) {
        memcpy(map->cubes + map->len, cube, sizeof(Cube_t));
        memcpy(map->posMat + map->len, &mat, sizeof(mat4));
        memcpy(map->colors + map->len, &colors, sizeof(vec4));
        map->len += 1;
        return;
    }

    size_t newCap = map->capacity * 2;
    map->cubes = realloc(map->cubes, newCap * sizeof(Cube_t));
    map->posMat = realloc(map->posMat, newCap * sizeof(mat4));
    map->colors = realloc(map->colors, newCap * sizeof(vec4));
    memcpy(map->cubes + map->len, cube, sizeof(Cube_t));
    memcpy(map->posMat + map->len, &mat, sizeof(mat4));
    memcpy(map->colors + map->len, &colors, sizeof(vec4));
    map->len += 1;
    map->capacity = newCap;
}

void parseMap(char* mapData, Map_t* map)
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
        pushCube(map, &cube);

        line = strtok(NULL, ";");
    }
}

void readMap(char* mapPath, Map_t* map)
{
    char* mapData = loadFile(mapPath);
    parseMap(mapData, map);
    free(mapData);
}

void initMap(Map_t* map, uint numUnitWidth, uint numUnitHeight)
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

    map->cubes = malloc(9 * sizeof(Cube_t));
    map->posMat = malloc(9 * sizeof(mat4));
    map->colors = malloc(9 * sizeof(vec4));
    map->len = 0;
    map->capacity = 9;
    readMap("./map", map);

    glCreateVertexArrays(1, &map->vao);
    glCreateBuffers(1, &map->vbo);
    glCreateBuffers(1, &map->ebo);

    glNamedBufferStorage(map->vbo, 8 * sizeof(Vertex_t), vertices, 0);
    glNamedBufferStorage(map->ebo, 36 * sizeof(GLuint), indices, 0);

    glVertexArrayVertexBuffer(map->vao, 0, map->vbo, 0, sizeof(Vertex_t));
    glVertexArrayElementBuffer(map->vao, map->ebo);

    Shader_t shaderList[] = {
        newShader("shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);

    map->program = program;

    glEnableVertexArrayAttrib(map->vao, 0);
    glVertexArrayAttribFormat(map->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(map->vao, 0, 0);

    mat4 base = { (vec4) { 1, 0, 0, 0 }, (vec4) { 0, 0, -1, 0 }, (vec4) { 0, 1, 0, 0 }, (vec4) { 0, 0, 0, 1 } };
    mat4 center = translationMat4((vec4) { ((float)numUnitWidth / 2), 0, (float)numUnitHeight / 2, 0 });
    base = multiplyMat4(&base, &center);
    mat4 proj = orthoMat4(0, numUnitWidth, 0, numUnitHeight, 0, 100);

    setUniformMat4(map->program.name, "base", &base);
    setUniformMat4(map->program.name, "proj", &proj);

    setUniformMat4v(map->program.name, "posMats", map->posMat, map->len);
    setUniform4fv(map->program.name, "colors", (float*)map->colors, map->len);
}

void renderMap(Map_t* map)
{
    glUseProgram(map->program.name);
    glBindVertexArray(map->vao);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, map->len);
}
