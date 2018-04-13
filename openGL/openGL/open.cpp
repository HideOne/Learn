#include "open.h"

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
" out vec4 vertexColor;\n "
"void main()\n"
"{\n"
"	gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"   vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

;

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
" in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"color = vertexColor;\n"
"}\n\0";

const GLchar* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.0, 0.0, 1.0);\n"
"}\n\0";


GLfloat g_vertices[] = {
	 //第一个三角形
	0.5f,  0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};

GLuint indices[] = {
	0, 1, 3,//第一个三角形
	1, 2, 3 //第二个三角形
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLStudy", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Create GLFW windows err" << std::endl;
		glfwTerminate();
		return -1;
	}

	//设置上下文为当前窗口
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "initiaklize GLew fail" << std::endl;
		return -1;
	}

	int width, heigh;
	glfwGetFramebufferSize(window, &width, &heigh);
	std::cout << width << "  " << heigh << std::endl;
	glViewport(0, 0, width, heigh);
	glfwSetKeyCallback(window, key_callBack);

	//生成一个缓冲ID
	GLuint VBO[2];
	glGenBuffers(2, VBO);

	//绑定定点缓冲类型
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	//把用户定义的数据复制到当前绑定缓冲的函数
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

	//创建着色器对象
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//把这个着色器源码附加到着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//编译shader
	glCompileShader(vertexShader);


	GLuint vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader1, 1, &vertexShaderSource, NULL);
	//编译shader
	glCompileShader(vertexShader1);


	//检测shader是否编译成功
	GLint  success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "shader ERR" << infoLog << std::endl;
	}
	else
	{
		Log("successful");
	}


	//定义并编译片段着色器
	GLuint fragmentShader, fragmentShader1;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader);
	glCompileShader(fragmentShader1);
	GLchar infoLog1[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "GL_FRAGMENT_SHADER ERR" << infoLog1 << std::endl;
	}
	else
	{
		Log("successful");
	}

	//创建一个着色器程序对象
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	GLuint shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader1);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "shader ERR" << infoLog << std::endl;
	}

	//查看上限
	int max;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);
	std::cout << max << std::endl;

	//激活着色器程序
	//glUseProgram(shaderProgram);

	// 删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//告诉OpenGL如何解析顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	/*// 0. 复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

	// 1. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 2. 当我们渲染一个物体时要使用着色器程序
	glUseProgram(shaderProgram);

	//3.绘制物体
	//someOpenGLFunctionThatDrawsOurTriangle()
	*/

	GLfloat points[] = {
		0.2f, 0.2f, 0,
		0.2f, -0.2f, 0,
		-0.2f, 0.2f, 0,

	};

	GLfloat endPoints[] = {
		-0.2f, 0.2f, 0,
		-0.6f, 0.2f, 0,
		-0.6f, -0.2f, 0,
	};

	

	// 创建一个VAO
	GLuint VAO[2], EBO;
	glGenVertexArrays(2, VAO);
	//1.绑定VAO1
	glBindVertexArray(VAO[0]);
	//2.把顶点数组复制到缓冲中供Opengl使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	//3.设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	//1.绑定VAO2
	glBindVertexArray(VAO[1]);
	//2.把顶点数组复制到缓冲中供Opengl使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(endPoints), endPoints, GL_STATIC_DRAW);
	//3.设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	

// 	GLuint VAO1, VBO1;
// 	glGenBuffers(1, &VBO1);
// 	//绑定定点缓冲类型
// 	glGenVertexArrays(1, &VAO1);
// 	//绑定VAO1
// 	glBindVertexArray(VAO1);
// 	
// 	//3.设置顶点属性指针
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
// 	//解绑VAO
// 	glBindVertexArray(0);
// 
// 	//绑定定点缓冲类型
// 	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
// 	//把顶点复制缓冲
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		//检查事件
		glfwPollEvents();

		//渲染指令
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//绘制物体
		glUseProgram(shaderProgram1);
#if 1

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//指明我们从索引缓冲渲染
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		//glBindVertexArray(0);
#endif

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//交换缓冲
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}


void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		//glfwSetWindowTitle(window, "hello...");
	}
}

void Log(char *info)
{
	if (info == NULL)
	{
		return;
	}
	std::cout << "=====" << info << "=====" << std::endl;
}