#version 460 core

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec3 vCol;

uniform mat4 tr;
uniform mat4 rot;
uniform mat4 rot2;
uniform mat4 proj;

out vec3 vertex_Color;

void main()
{
    gl_Position = proj * tr * rot * rot2 * vPos;
    vertex_Color = vCol;
}
