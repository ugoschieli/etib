#include "state.h"

void tick(GameState_t* state)
{
    float time = glfwGetTime();
    state->deltaTime = time - state->lastTime;
    state->lastTime = time;
}

void handleKeys(GameState_t* state)
{
    if (state->keyState.right == true) {
        state->cube.x += state->deltaTime * 1;
    }
    if (state->keyState.left == true) {
        state->cube.x -= state->deltaTime * 1;
    }
}
