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

GLfloat colors[] = {
    1, 0, 0, 1, 0, 0, //
    0, 1, 0, 0, 1, 0, //
    0, 0, 1, 0, 0, 1, //
    1, 0, 1, 1, 0, 1, //
    1, 1, 0, 1, 1, 0, //
    0, 1, 1, 0, 1, 1, //
};

int NUM_UNIT_WIDTH = 0;
int NUM_UNIT_HEIGHT = 0;

static void cubeInit(Cube_t* cube)
{
    glEnableVertexArrayAttrib(cube->vao, 0);
    glVertexArrayAttribFormat(cube->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(cube->vao, 0, 0);

    mat4 base = initMat4((vec4) { 1, 0, 0, 0 }, (vec4) { 0, 0, -1, 0 }, (vec4) { 0, 1, 0, 0 }, (vec4) { 0, 0, 0, 1 });
    mat4 proj = orthoMat4(0, NUM_UNIT_WIDTH, 0, NUM_UNIT_HEIGHT, 0, 100);

    setUniformMat4(cube->program->name, "base", &base);
    setUniformMat4(cube->program->name, "proj", &proj);

    setUniform3fv(cube->program->name, "colors", colors, 12);
}

CubeGlobal_t state_g = { 0 };

int main(void)
{
    glfwInit();
    gl3wInit();

    Window_t w = initWindow();
    NUM_UNIT_WIDTH = 10;
    NUM_UNIT_HEIGHT = NUM_UNIT_WIDTH / w.aspectRatio;
    glfwSetKeyCallback(w.w, handleKeys);
    glfwMakeContextCurrent(w.w);

    initGlobalState(&state_g);

    Shader_t shaderList[] = {
        newShader("shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);
    Program_t program2 = newProgram(shaderList, 2);

    Cube_t cube = newCube(&state_g, &program, cubeInit);
    Cube_t cube2 = newCube(&state_g, &program2, cubeInit);

    mat4 tr = translationMat4((vec4) { (float)NUM_UNIT_WIDTH / 2, 3, (float)NUM_UNIT_HEIGHT / 2, 0 });
    mat4 tr2 = translationMat4((vec4) { (float)NUM_UNIT_WIDTH / 2 + 2, 3, (float)NUM_UNIT_HEIGHT / 2, 0 });
    setUniformMat4(cube.program->name, "tr", &tr);
    setUniformMat4(cube2.program->name, "tr", &tr2);

    vec4 axis = { 0, 1, 1, 0 };
    normalizeVec4(&axis);

    while (!glfwWindowShouldClose(w.w)) {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        mat4 rot = rotationMat4(axis, glfwGetTime());
        /*mat4 rot = rotationMat4(axis, 0);*/

        setUniformMat4(cube.program->name, "rot", &rot);
        setUniformMat4(cube2.program->name, "rot", &rot);

        renderCube(&cube);
        renderCube(&cube2);

        glfwSwapBuffers(w.w);
        glfwPollEvents();
    }

    glfwDestroyWindow(w.w);
    glfwTerminate();
    return 0;
}
