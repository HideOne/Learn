#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec3 ourColor;
in vec3 outPos;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float point = 0.2;

void main()
{
FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, vec2(TexCoord.x, TexCoord.y)), point);
}