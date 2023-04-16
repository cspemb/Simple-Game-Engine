#version 330 core
in vec3 vPosition;
in vec3 vColor;
uniform mat4 vTransform;
out vec3 color;

void main()
{
    gl_Position = vTransform * vec4(vPosition, 1.0) ;
    color = vColor;
}