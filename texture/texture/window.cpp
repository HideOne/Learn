#include "window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Command.h"

window* window::S_win = NULL;


window::window()
{
}


window::~window()
{
}

window* window::getInstance()
{
	if (!S_win)
	{
		S_win = new window;
		S_win->loop = NULL;
	}
	return S_win;
}

void window::initWindow(const int width, const int heigh, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ����opengl���Ĺ���
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//�̶����ڴ�С
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "111", NULL, NULL);
	if (window == NULL)
	{
		LOG("window create fail");
		glfwTerminate();
		exit(-1);
	}
	LOG("�������ڳɹ�!")
	//����������Ϊ��ǰ����
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG("Failed to initialize GLAD");
		exit(-1);
	}


	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, window::SizeCallBack);
	
	//glViewport(0, 0, width, heigh);
	while (!glfwWindowShouldClose(window))
	{
		//����¼�
		glfwPollEvents();
		//��������
		glfwSwapBuffers(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		loop();

	}

	glfwTerminate();
}

void window::SizeCallBack(GLFWwindow* wind, int width, int height)
{
	glViewport(0, 0, width, height);
	
}
