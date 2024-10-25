#include <math.h>
#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>

#include "shaders.h"
#include "triangles.h"
#include "mat4.h"
#include "uniform.h"
#include "window.h"

static void handleKeys(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(w, true);
    }
}

static void triInit(GLuint vao)
{
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 0);
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
        newShader("shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Shader_t shaderList2[] = {
        newShader("shaders/vshader2.glsl", GL_VERTEX_SHADER),
        newShader("shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);
    Program_t program2 = newProgram(shaderList2, 2);

    // stride = size in bytes between the beginning of two vertex (here 6 * sizeof(GLfloat)) (sizeof(vertex))
    // first attrib position: offset 0
    // second attrib color: offset 3 * sizeof(GLfloat)
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // first vertex
        0.0f, 0.37f, 0.0f, 0.0f, 1.0f, 0.0f, // second vertex
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // third vertex
    };

    GLuint indices[] = { 0, 1, 2 };

    Triangle_t tri = newTriangle(vertices, 18, indices, &program, triInit);
    Triangle_t tri2 = newTriangle(vertices, 18, indices, &program2, triInit);

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
