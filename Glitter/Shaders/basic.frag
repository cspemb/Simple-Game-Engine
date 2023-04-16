#version 330 core
in vec3 color;
out vec4 ColorOut;
uniform vec3 colorMask;

void main()
{
    ColorOut = vec4(colorMask * color, 1.0f);
}