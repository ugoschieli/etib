#ifndef STATE_H
#define STATE_H

#include "map.h"
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
