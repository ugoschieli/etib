#ifndef MAP_H
#define MAP_H

#include "state.h"

typedef struct Vertex {
    float x;
    float y;
    float z;
} Vertex_t;

void initMap(GameState_t* state);

void renderMap(GameState_t* state);

#endif // MAP_H
