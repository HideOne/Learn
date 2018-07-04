#include "shader.h"
#include "DrawPic.h"

enum object
{
	VOB, VAO, EBO
}object;


GLFWwindow* createGLFWWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef MACX
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(800, 600, "again", NULL, NULL);
	if (window == NULL)
	{
		LOG("cuowu");
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	return window;
}

void Frame_Size_CallBack(GLFWwindow* window, int width, int heigt)
{
	glViewport(0, 0, width, heigt);
}

void mainLoop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		//输入 
		processInput(window);

		//渲染
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}


//接收用户输入并作出响应
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void CreateShader(int* vertexShader, char const *string, GLenum type)
{
	//编译着色器
	*vertexShader = glCreateShader(type);
	//把色器源码附加到着色器对象上
	glShaderSource(*vertexShader, 1, &string, NULL);
	//编译着色器
	glCompileShader(*vertexShader);

	int ret;
	char info[512];
	glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &ret);
	if (!ret)
	{
		glGetShaderInfoLog(*vertexShader, 512, NULL, info);
		if (type == GL_VERTEX_SHADER)
		{
			LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
			LOG(info);
		}
		else
		{
			LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
			LOG(info);
		}
	}

}

void CreateShaderProgram(unsigned int *shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);


	int ret;
	char info[512];
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &ret);
	if (!ret)
	{
		glGetShaderInfoLog(*shaderProgram, 512, NULL, info);
		LOG("ERROR::SHADER::LINK::COMPILATION_FAILED");
		LOG(info);
	}
}

