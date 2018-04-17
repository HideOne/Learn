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

private:
	void compile(const GLchar* vertexCode, const GLchar* fragmentCode);
	GLuint CreateShader(char const *code, GLenum ShderType);
	GLuint CreateShaderProcess(GLint vertexShade, GLint fragmentShaderr);
};

#endif