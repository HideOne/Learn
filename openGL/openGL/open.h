#define GLEW_STATIC
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"


void Log(char *info);

void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode);