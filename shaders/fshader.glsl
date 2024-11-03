#version 460 core

uniform vec3 colors[12];

out vec4 fColor;

void main()
{
    fColor = vec4(colors[gl_PrimitiveID], 1.0);
}
