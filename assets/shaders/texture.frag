#version 460 core

in vec4 fColor;
in vec2 fTexCoords;
flat in int iTexId;

uniform sampler2D uTextures[8];

out vec4 color;

void main()
{
    if(iTexId >= 0) {
        color = fColor;
    }
    else {
        color = fColor;
    }
}