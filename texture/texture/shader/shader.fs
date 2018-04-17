#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec3 ourColor;
in vec3 outPos;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord),0.2);
}