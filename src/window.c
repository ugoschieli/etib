#include "window.h"

Window_t initWindow(GameState_t* state, GLFWkeyfun keyCb)
{
    Window_t window = { 0 };
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(mode->width, mode->height, "Etib", monitor, 0);

    glfwSetKeyCallback(w, keyCb);
    glfwMakeContextCurrent(w);
    glfwSwapInterval(1);

    window = (Window_t) {
        .w = w,
        .monitor = monitor,
        .width = mode->width,
        .height = mode->height,
        .aspectRatio = (float)mode->width / mode->height,
        .refreshRate = mode->refreshRate
    };

    state->window = window;
    state->numUnitWidth = 10;
    state->numUnitHeight = state->numUnitWidth / window.aspectRatio;

    return window;
}
