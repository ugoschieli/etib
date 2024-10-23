#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>
#include <math.h>

#define LOG_H_IMPL
#include "log.h"
#include "shaders.h"
#include "triangles.h"
#include "mat4.h"
#include "uniform.h"

typedef struct Window {
    GLFWwindow* w;
    GLFWmonitor* monitor;
    int width;
    int height;
    float aspectRatio;
    int refreshRate;
} Window_t;

static void handleKeys(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(w, true);
    }
}

static Window_t initWindow(void)
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

    Window_t w = initWindow();
    const int NUM_UNIT_WIDTH = 10;
    const int NUM_UNIT_HEIGHT = NUM_UNIT_WIDTH / w.aspectRatio;
    glfwSetKeyCallback(w.w, handleKeys);
    glfwMakeContextCurrent(w.w);

    Shader_t shaderList[] = {
        newShader("src/shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("src/shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Shader_t shaderList2[] = {
        newShader("src/shaders/vshader2.glsl", GL_VERTEX_SHADER),
        newShader("src/shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);
    Program_t program2 = newProgram(shaderList2, 2);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.37f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    Triangle_t tri = newTriangle(vertices, 18, &program, triInit);
    Triangle_t tri2 = newTriangle(vertices, 18, &program2, triInit);

    while (!glfwWindowShouldClose(w.w)) {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        mat4 tr = translationMat4((vec4) { (float)NUM_UNIT_WIDTH / 2, (float)NUM_UNIT_HEIGHT / 2, -10, 0 });
        mat4 rot = rotationMat4((vec4) { 0, 1, 0, 0 }, glfwGetTime());
        mat4 rot2 = rotationMat4((vec4) { 0, 1, 0, 0 }, M_PI / 2);
        mat4 proj = orthoMat4(0, NUM_UNIT_WIDTH, 0, NUM_UNIT_HEIGHT, 0, 100);

        setUniformMat4(tri.program->name, "tr", &tr);
        setUniformMat4(tri.program->name, "rot", &rot);
        setUniformMat4(tri.program->name, "proj", &proj);

        setUniformMat4(tri2.program->name, "tr", &tr);
        setUniformMat4(tri2.program->name, "rot", &rot);
        setUniformMat4(tri2.program->name, "rot2", &rot2);
        setUniformMat4(tri2.program->name, "proj", &proj);

        renderTriangle(&tri);
        renderTriangle(&tri2);

        glfwSwapBuffers(w.w);
        glfwPollEvents();
    }

    glfwDestroyWindow(w.w);
    glfwTerminate();
    return 0;
}
