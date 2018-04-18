#ifndef __SHADERCOMPILER_H__
#define __SHADERCOMPILER_H__
#include "glad/glad.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class ShaderCompiler
{
public:
	ShaderCompiler(const GLchar* vertextPath, const GLchar* fragmentPath);
	~ShaderCompiler();
	void useProgram();
	GLuint ID;
	void setInt(const char* name, const int num);
	void setFloat(const char* name, const float num);
	void addApche(const char* name)
	{
		if (aphce >= 1.0f)
		{
			return;
		}
		aphce += (float)0.1;
		setFloat(name, aphce);
	}
	void Subtract(const char* name)
	{
		if (aphce <= 0.0f)
		{
			return;
		}
		aphce -= (float)0.1;
		setFloat(name, aphce);
	}

	float aphce;

private:
	void compile(const GLchar* vertexCode, const GLchar* fragmentCode);
	GLuint CreateShader(char const *code, GLenum ShderType);
	GLuint CreateShaderProcess(GLint vertexShade, GLint fragmentShaderr);
};

#endif