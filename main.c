#include <stdbool.h>
#include "GL/gl3w.h"
#include <GLFW/glfw3.h>

#include "shaders.h"
#include "cube.h"
#include "mat4.h"
#include "uniform.h"
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

GLfloat colors[] = {
    1, 0, 0, 1, 0, 0, //
    0, 1, 0, 0, 1, 0, //
    0, 0, 1, 0, 0, 1, //
    1, 0, 1, 1, 0, 1, //
    1, 1, 0, 1, 1, 0, //
    0, 1, 1, 0, 1, 1, //
};

static void cubeInit(Cube_t* cube)
{
    glEnableVertexArrayAttrib(cube->vao, 0);
    glVertexArrayAttribFormat(cube->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(cube->vao, 0, 0);

    mat4 base = { (vec4) { 1, 0, 0, 0 }, (vec4) { 0, 0, -1, 0 }, (vec4) { 0, 1, 0, 0 }, (vec4) { 0, 0, 0, 1 } };
    mat4 center = translationMat4((vec4) { ((float)STATE.numUnitWidth / 2), 0, (float)STATE.numUnitHeight / 2, 0 });
    base = multiplyMat4(&base, &center);
    mat4 proj = orthoMat4(0, STATE.numUnitWidth, 0, STATE.numUnitHeight, 0, 100);

    setUniformMat4(cube->program->name, "base", &base);
    setUniformMat4(cube->program->name, "proj", &proj);

    setUniform3fv(cube->program->name, "colors", colors, 12);
}

CubeGlobal_t cube_state_g = { 0 };

int main(void)
{
    glfwInit();
    gl3wInit();

    glfwSetErrorCallback(errorCallback);

    initWindow(&STATE, keyCallback);
    initGlobalState(&cube_state_g);

    Shader_t shaderList[] = {
        newShader("shaders/vshader.glsl", GL_VERTEX_SHADER),
        newShader("shaders/fshader.glsl", GL_FRAGMENT_SHADER)
    };

    Program_t program = newProgram(shaderList, 2);

    STATE.cube = newCube(&cube_state_g, &program, cubeInit);

    vec4 axis = { 0, 1, 1, 0 };
    normalizeVec4(&axis);

    while (!glfwWindowShouldClose(STATE.window.w)) {
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearBufferfv(GL_COLOR, 0, (float[]) { 0.0f, 0.0f, 0.0f, 0.0f });

        tick(&STATE);
        handleKeys(&STATE);

        mat4 tr = translationMat4((vec4) { STATE.cube.x, STATE.cube.y + 3, STATE.cube.z, 0 });
        setUniformMat4(STATE.cube.program->name, "tr", &tr);

        mat4 rot = rotationMat4(axis, glfwGetTime());
        setUniformMat4(STATE.cube.program->name, "rot", &rot);

        renderCube(&STATE.cube);

        glfwSwapBuffers(STATE.window.w);
    }

    glfwDestroyWindow(STATE.window.w);
    glfwTerminate();
    return 0;
}
