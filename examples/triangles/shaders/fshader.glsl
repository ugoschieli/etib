#version 460 core

in vec3 vertex_Color;

out vec4 fColor;

void main()
{
    fColor = vec4(vertex_Color, 1.0);
}
