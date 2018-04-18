#include <iostream>
#include "glad/glad.h"
#include "window.h"
#include "Command.h"
#include "GLFW/glfw3.h"
#include "ShaderCompiler.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void processInput(GLFWwindow* win,  ShaderCompiler* shader);

float vertices1[] = {
	//位置						颜色			  纹理
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,//左下角
	0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f
};

float texCoords[] = {
	0.0f, 0.0f,//左下角
	1.0f, 0.0f,
	0.5f, 1.0f
};

int main()
{

	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

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


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//紋理屬性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//生成文理
	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//为当前文理对象设置环绕,过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	//加载并执行文理
	int width, heigh, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char *data = stbi_load("wall.jpg" , &width, &heigh, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("load text ERR" << __LINE__);
	}
	stbi_image_free(data);


	//生成文理
	GLuint texture1;
	glGenTextures(1, &texture1);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//为当前文理对象设置环绕,过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//加载并执行文理
	unsigned char *data1 = stbi_load("awesomeface.png", &width, &heigh, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("load text ERR" << __LINE__);
	}
	stbi_image_free(data1);

	shader.useProgram();
	shader.setInt("ourTexture", 0);
	shader.setInt("ourTexture2", 1);

	//告诉OpenGL新的顶点格式

 	//glBindTexture(GL_TEXTURE_2D, texture);
    //glBindVertexArray(VAO);

	//将向量(1, 0, 0)位移(1,1,0)个单位
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	
	vec = trans * vec;
	LOG(vec.x << "  " << vec.y << " " << vec.z);
	

	//将文理逆时针旋转90度。然后缩放0.5倍
	
	//LOG(trans1.length());
	//trans1 = glm::rotate(trans1, glm::radians(90.f), glm::vec3(0.0, 0.0, -1.0));
	
	//trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0));
    //trans1 = glm::rotate(trans1, glm::radians(90.0f), glm::vec3(0.0, 0.0, -1.0));
	//trans1 += glm::scale(trans1, glm::vec3(0.5, 0.5, 0.5));
	
	//glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans1));

	//glViewport(0, 0, width, heigh);
	while (!glfwWindowShouldClose(win->win))
	{
		processInput(win->win, &shader);

		//检查事件
		glfwPollEvents();
		//交换缓冲
		glfwSwapBuffers(win->win);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glm::mat4 trans1;
		trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0));
		trans1 = glm::rotate(trans1, (float)glfwGetTime(), glm::vec3(0.0, 0.0, -1.0));
		//trans1 += glm::scale(trans1, glm::vec3(0.5, 0.5, 0.5));

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans1));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		//shader.useProgram();
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	
	}


	delete win;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void processInput(GLFWwindow* win,  ShaderCompiler* shader)
{
	if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
	{
		shader->addApche("point");
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		shader->Subtract("point");
	}
}
