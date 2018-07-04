#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

extern enum object;

#define LOG(info) \
{\
  std::cout<<"====="<<info<<"====="<<std::endl; \
}

GLFWwindow* createGLFWWindow();


//窗口大小改变的回调函数 窗口大小改变时相应改变视口大小
void Frame_Size_CallBack(GLFWwindow* window, int width, int heigt);


void mainLoop(GLFWwindow* window);

//接收输入
void processInput(GLFWwindow* window);

void CreateShader(int* vertexShader, char const *string, GLenum type);

void CreateShaderProgram(unsigned int *shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);