#include <iostream>
#include "window.h"
#include "Command.h"
#include "GLFW/glfw3.h"




void lad()
{
	
}


int main()
{

	window* win = window::getInstance();
	win->loop = lad;
	win->initWindow(800, 600, "texture");
	

	return 0;
}


