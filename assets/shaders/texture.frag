#version 460 core

in vec4 fColor;
in vec2 fTexCoords;

uniform sampler2D texture1;

out vec4 FragColor;

void main()
{
    FragColor = texture(texture1, fTexCoords);
}