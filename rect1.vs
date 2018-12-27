#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;    // 输入材质坐标

uniform float ourX;
uniform float ourY;

out vec2 TexCoord;  // 输出材质坐标

void main()
{
   gl_Position = vec4(aPos.x+ourX, aPos.y+ourY, 0.0f, 1.0f);
   TexCoord = aTexCoord;
}