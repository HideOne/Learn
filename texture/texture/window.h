#ifndef __WINDOW_H__
#define __WINDOW_H__
struct GLFWwindow;

typedef void(*glLoop)();

class window
{
public:
	static window* getInstance();
	void initWindow(const int width, const int heigh, const char* title);
	glLoop loop;
	~window();
	
private:
	static void SizeCallBack(GLFWwindow* wind, int width, int height);
	window();
	static window* S_win;
};


#endif
