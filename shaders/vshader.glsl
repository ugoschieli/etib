#version 460 core

layout (location = 0) in vec4 vPos;

uniform mat4 tr;
uniform mat4 rot;
uniform mat4 base;
uniform mat4 proj;

void main()
{
    gl_Position = proj * base * tr * rot * vPos;
}
