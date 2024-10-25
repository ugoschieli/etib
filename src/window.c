#include "window.h"
#include "log.h"

Window_t initWindow(void)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    print_debug("Refresh rate: %d", mode->refreshRate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(mode->width, mode->height, "Etib", monitor, 0);

    return (Window_t) {
        .w = w,
        .monitor = monitor,
        .width = mode->width,
        .height = mode->height,
        .aspectRatio = (float)mode->width / mode->height,
        .refreshRate = mode->refreshRate
    };
}
