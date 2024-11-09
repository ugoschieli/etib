#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>

#include "map.h"
#include "window.h"
#include "log.h"
#include "state.h"

#define REGISTER_KEY(glfwKey, stateKey)             \
    if (key == glfwKey && action == GLFW_PRESS) {   \
        STATE.keyState.stateKey = true;             \
    }                                               \
    if (key == glfwKey && action == GLFW_RELEASE) { \
        STATE.keyState.stateKey = false;            \
    }

GameState_t STATE = { 0 };

static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(w, true);
    }

    REGISTER_KEY(GLFW_KEY_RIGHT, right);
    REGISTER_KEY(GLFW_KEY_LEFT, left);
}

void errorCallback(int error, const char* desc)
{
    (void)error;
    print_error("Glfw error: %s", desc);
}

int main(void)
{
    glfwInit();
    gl3wInit();

    glfwSetErrorCallback(errorCallback);

    initWindow(&STATE, keyCallback);
    initMap(&STATE.map, STATE.numUnitWidth, STATE.numUnitHeight);

    while (!glfwWindowShouldClose(STATE.window.w)) {
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        tick(&STATE);
        handleKeys(&STATE);

        renderMap(&STATE.map);

        glfwSwapBuffers(STATE.window.w);
    }

    glfwDestroyWindow(STATE.window.w);
    glfwTerminate();
    destroyState(&STATE);
    return 0;
}
