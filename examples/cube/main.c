#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>

#include "shaders.h"
#include "cube.h"
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

    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(vao, 0, 0);
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

    Program_t program = newProgram(shaderList, 2);

    Vertex_t vertices[] = {
        (Vertex_t) { -0.5, -0.5, -0.5 }, // left bottom front 0
        (Vertex_t) { 0.5, -0.5, -0.5 }, // right bottom front 1
        (Vertex_t) { -0.5, -0.5, 0.5 }, // left up front      2
        (Vertex_t) { 0.5, -0.5, 0.5 }, // right up front      3

        (Vertex_t) { -0.5, 0.5, -0.5 }, // left bottom back 4
        (Vertex_t) { 0.5, 0.5, -0.5 }, // right bottom back 5
        (Vertex_t) { -0.5, 0.5, 0.5 }, // left up back      6
        (Vertex_t) { 0.5, 0.5, 0.5 }, // right up back      7
    };

    GLfloat colors[] = {
        1, 0, 0, 1, 0, 0, //
        0, 1, 0, 0, 1, 0, //
        0, 0, 1, 0, 0, 1, //
        1, 0, 1, 1, 0, 1, //
        1, 1, 0, 1, 1, 0, //
        0, 1, 1, 0, 1, 1, //
    };

    GLuint indices[] = {
        0, 1, 3, // first triangle front face
        3, 2, 0, // second triangle front face

        0, 2, 6, // first triangle left face
        6, 4, 0, // second triangle left face

        1, 3, 7, // first triangle right face
        7, 5, 1, // second triangle right face

        4, 5, 7, // first triangle back face
        7, 6, 4, // second triangle back face

        2, 3, 7, // first triangle up face
        7, 6, 2, // second triangle up face

        0, 1, 5, // first triangle bottom face
        5, 4, 0, // second triangle bottom face
    };

    Cube_t cube = newCube(vertices, sizeof(vertices), indices, &program, triInit);

    mat4 base = initMat4((vec4) { 1, 0, 0, 0 }, (vec4) { 0, 0, -1, 0 }, (vec4) { 0, 1, 0, 0 }, (vec4) { 0, 0, 0, 1 });

    mat4 tr = translationMat4((vec4) { (float)NUM_UNIT_WIDTH / 2, 3, (float)NUM_UNIT_HEIGHT / 2, 0 });
    mat4 proj = orthoMat4(0, NUM_UNIT_WIDTH, 0, NUM_UNIT_HEIGHT, 0, 100);

    setUniformMat4(cube.program->name, "tr", &tr);
    setUniformMat4(cube.program->name, "base", &base);
    setUniformMat4(cube.program->name, "proj", &proj);

    setUniform3fv(cube.program->name, "colors", colors, 12);

    vec4 axis = { 0, 1, 1, 0 };
    normalizeVec4(&axis);

    while (!glfwWindowShouldClose(w.w)) {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        mat4 rot = rotationMat4(axis, glfwGetTime());
        /*mat4 rot = rotationMat4(axis, 0);*/

        setUniformMat4(cube.program->name, "rot", &rot);

        renderCube(&cube);

        glfwSwapBuffers(w.w);
        glfwPollEvents();
    }

    glfwDestroyWindow(w.w);
    glfwTerminate();
    return 0;
}
