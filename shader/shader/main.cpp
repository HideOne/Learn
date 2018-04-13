#include "shader.h"
#include "DrawPic.h"
#include "ShaderManager.h"

float vertices[] = {
	//位置               颜色
	-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
};

float points[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"//out vec4 vertexColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"//vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"ourColor = aColor;\n"
"}\n\0";

char* fragmentShaderSource = {
	"\
		#version 330 core\n\
			out vec4 FragColor;\n\
			in vec4 vertexColor;\n\
			in vec3 ourColor;\n\
			void main()\n\
			{\n\
			FragColor = vec4(ourColor, 1.0);\n\
			}\n\
	"
};


char* uniform = {
	"\
		#version 330 core\
		out vec4 FragColor;\
		uniform vec4 ourColor;//在opengl程序代码中设定这个变量\
		void main()\
		{\
		FragColor = ourColor;\
		}\
	"
};


extern float vertices[];

extern enum object;

int main()
{
	GLFWwindow* window = createGLFWWindow();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//注册窗口尺寸改变回调函数
	glfwSetFramebufferSizeCallback(window, Frame_Size_CallBack);

	//生成 初始化VBO对象 
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#if 0
	//顶点着色器
	int vertexShader;
	CreateShader(&vertexShader, vertexShaderSource, GL_VERTEX_SHADER);

	//片段着色器
	int fragmentShader;
	CreateShader(&fragmentShader, fragmentShaderSource, GL_FRAGMENT_SHADER);

	//创建着色器程序
	unsigned int shaderProgram = 0;
	CreateShaderProgram(&shaderProgram, vertexShader, fragmentShader);

#endif
	
	ShaderManager shader("shader/shader.vs", "shader/shader.fs");


	int vertexPosLocation = glGetUniformLocation(shader.ID, "offset");
	glUseProgram(shader.ID);
	glUniform4f(vertexPosLocation, 0.3f, 0.0f, 0.0f, 1.0f);

	//创建VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//把顶点复制到缓冲中
#if 0
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//设置顶点属性指针
	//告诉OpenGL该如何解析顶点数据
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//创建EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	

	while (!glfwWindowShouldClose(window))
	{
		//输入 
		processInput(window);

		//渲染
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		shader.use();

		//更新uniform颜色
		//设置uniform
		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
		//glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, greenValue, greenValue, 0.0f, 1.0f);


#if 1
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
#else
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}






	//释放资源
	glfwTerminate();
	LOG("hello");
	return 0;
}