#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "mat4.h"
#include "vec4.h"
#include "shaders.h"

struct GameState_t;

typedef struct Vertex {
    float x;
    float y;
    float z;
} Vertex_t;

typedef struct Color {
    float r;
    float g;
    float b;
} Color_t;

typedef struct Position {
    float x;
    float y;
    float z;
} Position_t;

typedef struct Cube {
    Position_t pos;
    Color_t color;
} Cube_t;

typedef struct Map {
    uint vao;
    Program_t program;
    uint vbo;
    uint ebo;
    size_t len;
    size_t capacity;
    Cube_t* cubes;
    mat4* posMat;
    vec4* colors;
} Map_t;

void initMap(Map_t* map, uint numUnitWidth, uint numUnitHeight);

void renderMap(Map_t* map);

#endif // MAP_H
