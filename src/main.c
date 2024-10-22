#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>

#define LOG_H_IMPL
#define SHADER_H_IMPL
#include "shader.h"
#include "triangles.h"

void handleKeys(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(w, true);
    }
}

GLFWwindow* initWindow()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    print_debug("Refresh rate: %d", mode->refreshRate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(mode->width, mode->height, "Etib", monitor, 0);

    return w;
}

int main()
{
    glfwInit();
    gl3wInit();

    GLFWwindow* w = initWindow();
    glfwSetKeyCallback(w, handleKeys);
    glfwMakeContextCurrent(w);

    Shader_t shaderList[] = {
        newShader("src/shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("src/shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);

    const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    Triangle_t tri = newTriangle((GLfloat*)vertices, 18, &program);

    while (!glfwWindowShouldClose(w)) {
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        renderTriangle(&tri);

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwDestroyWindow(w);
    glfwTerminate();
    return 0;
}
