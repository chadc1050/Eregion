#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexId;

uniform mat4 uCam;

out vec4 fColor;
out vec2 fTexCoords;
out int iTexId;

void main()
{
    fColor = aColor;
    fTexCoords = aTexCoords;
    iTexId = int(aTexId);
    gl_Position = uCam * vec4(aPos, 0.0, 1.0);
}
