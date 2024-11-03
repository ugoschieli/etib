#ifndef STATE_H
#define STATE_H

#include "shaders.h"
#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef struct KeyState {
    bool right;
    bool left;
} KeyState_t;

typedef struct Window {
    GLFWwindow* w;
    GLFWmonitor* monitor;
    int width;
    int height;
    float aspectRatio;
    int refreshRate;
} Window_t;

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
} Map_t;

typedef struct GameState {
    float deltaTime;
    float lastTime;
    Window_t window;
    int numUnitWidth;
    int numUnitHeight;
    KeyState_t keyState;
    Map_t map;
} GameState_t;

void tick(GameState_t* state);

void handleKeys(GameState_t* state);

void destroyState(GameState_t* state);

#endif // STATE_H
