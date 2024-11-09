#version 460 core

layout (location = 0) in vec4 vPos;

uniform mat4 posMats[9];
uniform vec4 colors[9];
uniform mat4 base;
uniform mat4 proj;

out vec4 color;

void main()
{
    gl_Position = proj * base * posMats[gl_InstanceID] * vPos;
    color = colors[gl_InstanceID];
}
