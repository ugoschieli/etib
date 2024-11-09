#include "state.h"

#include "stdlib.h"

void tick(GameState_t* state)
{
    float time = glfwGetTime();
    state->deltaTime = time - state->lastTime;
    state->lastTime = time;
}

void handleKeys(GameState_t* state)
{
    (void)state;
}

void destroyState(GameState_t* state)
{
    free(state->map.cubes);
    free(state->map.posMat);
    free(state->map.colors);
}
