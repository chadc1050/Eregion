#version 460 core
in vec3 color;
out vec4 fragment;
void main()
{
    fragment = vec4(color, 1.0);
}