#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // 混合颜色与通道, 效率极其低
    FragColor = vec4(texture(texture1, TexCoord).r, texture(texture1, TexCoord).g, texture(texture1, TexCoord).b, texture(texture2, TexCoord));
}