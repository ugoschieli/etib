#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>
#include <math.h>

#define LOG_H_IMPL
#include "log.h"
#include "shaders.h"
#include "triangles.h"
#include "mat4.h"

static void handleKeys(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(w, true);
    }
}

static GLFWwindow* initWindow(void)
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

static void triInit(void)
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

int main(void)
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

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    Triangle_t tri = newTriangle(vertices, 18, &program, triInit);

    while (!glfwWindowShouldClose(w)) {
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        /*mat4 rot = rotationMat4((vec4) { 0, 0, 1, 0 }, glfwGetTime());*/
        /*GLfloat rotBuf[16] = { 0 };*/
        /*toArrayMat4(&rot, rotBuf);*/
        /*GLint rotUniform = glGetUniformLocation(tri.program->name, "rot");*/
        /*glUniformMatrix4fv(rotUniform, 1, false, rotBuf);*/
        renderTriangle(&tri);

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwDestroyWindow(w);
    glfwTerminate();
    return 0;
}
