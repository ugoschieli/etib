#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"

typedef struct Window {
    GLFWwindow* w;
    GLFWmonitor* monitor;
    int width;
    int height;
    float aspectRatio;
    int refreshRate;
} Window_t;

Window_t initWindow(void);

#endif // WINDOW_H
