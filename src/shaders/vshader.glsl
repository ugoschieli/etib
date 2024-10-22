#version 460 core

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec3 vCol;

uniform mat4 rot;

out vec3 vertex_Color;

void main()
{
    gl_Position = vPos;
    vertex_Color = vCol;
}
