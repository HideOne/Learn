#ifndef SHADERMANAGER
#define SHADERMANAGER

 // !SHADERMANAGER
#include<glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

class ShaderManager
{
public:
	//读取并构建着色器
	ShaderManager();
	ShaderManager(const GLchar* vertexPath, const GLchar* fragmentPath);
	~ShaderManager();

	//使用激活程序
	void use();

	//uniform 工具函数怒
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void CompileShader(const char* vertexCode, const  char* fragmentCode);
	void setMat4(const std::string &name, const glm::mat4 &value);

	//程序ID
	unsigned int ID;

private:
	GLint CreateShader(char const *code, GLenum ShderType); 
	void CreateShaderProgram(GLint vertexShade, GLint fragmentShaderr);
};

#endif