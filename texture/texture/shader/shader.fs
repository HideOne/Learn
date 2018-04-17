#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec3 ourColor;
in vec3 outPos;
void main()
{
FragColor = vec4(ourColor, 1.0);
}