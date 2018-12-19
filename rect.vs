#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

uniform float ourX;
uniform float ourY;

out vec4 vertexColor;

void main()
{
   gl_Position = vec4(aPos.x+ourX, aPos.y+ourY, 0.0f, 1.0f);
   vertexColor = vec4(aColor.x, aColor.y,aColor.z, 1.0f);
}