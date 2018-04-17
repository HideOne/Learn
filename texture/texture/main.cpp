#include <iostream>
#include "glad/glad.h"
#include "window.h"
#include "Command.h"
#include "GLFW/glfw3.h"
#include "ShaderCompiler.h"

float vertices[] = {
	//位置               颜色
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

float texCoords[] = {
	0.0f, 0.0f,//左下角
	1.0f, 0.0f,
	0.5f, 1.0f
};

int main()
{

	window* win = window::getInstance();
	win->initWindow(800, 600, "texture");
	//return 0;
	
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	
	ShaderCompiler shader("shader/shader.vs", "shader/shader.fs");
	
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//glViewport(0, 0, width, heigh);
	while (!glfwWindowShouldClose(win->win))
	{
		//检查事件
		glfwPollEvents();
		//交换缓冲
		glfwSwapBuffers(win->win);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.useProgram();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}
	delete win;
	
}


