#include "ShaderCompiler.h"
#include "Command.h"

ShaderCompiler::ShaderCompiler(const GLchar* vertextPath, const GLchar* fragmentPath)
{
	std::string vertextCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertextPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertextCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
	
		LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");

	}

	compile(vertextCode.c_str(), fragmentCode.c_str());

}

ShaderCompiler::~ShaderCompiler()
{

}

void ShaderCompiler::useProgram()
{
	glUseProgram(ID);
}

void ShaderCompiler::setInt(const char* name, const int num)
{
	glUniform1i(glGetUniformLocation(ID, name), num);
}

void ShaderCompiler::compile(const GLchar* vertexCode, const GLchar* fragmentCode)
{
	if (strlen(vertexCode) < 5 || strlen(fragmentCode) < 5)
	{
		LOG("ERROR::compile");
		return;
	}

	GLuint vertex = this->CreateShader(vertexCode, GL_VERTEX_SHADER);
	GLuint fagment = this->CreateShader(fragmentCode, GL_FRAGMENT_SHADER);
	CreateShaderProcess(vertex, fagment);

}

GLuint ShaderCompiler::CreateShader(char const *code, GLenum ShderType)
{
	GLuint shader = glCreateShader(ShderType);
	GLint errnum;
	GLchar info[512] = { 0 };

	//把shader与代码绑定
	glShaderSource(shader, 1, &code, NULL);
	//编译代码
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &errnum);
	if (!errnum)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		LOG(info << code);
		return -1;
	}


	return shader;

}

GLuint ShaderCompiler::CreateShaderProcess(GLint vertexShade, GLint fragmentShader)
{
	ID = glCreateProgram();
	GLint errnum;
	GLchar info[512] = { 0 };

	glAttachShader(ID, vertexShade);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &errnum);
	if (!errnum)
	{
		glGetProgramInfoLog(ID, 512, NULL, info);
		LOG(info);
		return -1;
	}

	glDeleteShader(vertexShade);
	glDeleteShader(fragmentShader);

	return 0;
}
