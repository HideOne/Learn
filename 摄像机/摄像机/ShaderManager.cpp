
#include "ShaderManager.h"
#include "shader.h"


ShaderManager::ShaderManager()
{
}


ShaderManager::ShaderManager(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//从文件路径中获取顶点 片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件处理器
		
		vShaderFile.close();
		fShaderFile.close();
		// 转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	LOG(vShaderCode);
	LOG(fShaderCode);

	//着色器程序
	CompileShader(vShaderCode, fShaderCode);

}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::use()
{
	glUseProgram(ID);
}

void ShaderManager::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderManager::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderManager::setFloat(const std::string &name, float value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderManager::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	if (strlen(vertexCode) < 5 || strlen(fragmentCode) < 5)
	{
		LOG("code is err");
		return;
	}
	GLuint vertexShader = CreateShader(vertexCode, GL_VERTEX_SHADER);
	GLuint fragmentShader = CreateShader(fragmentCode, GL_FRAGMENT_SHADER);
	CreateShaderProgram(vertexShader, fragmentShader);
}

GLint ShaderManager::CreateShader(char const *code, GLenum ShderType)
{
	unsigned int shader = glCreateShader(ShderType);
	int buildRet;
	char buildInfo[512];

	//把shader代码与shader绑定
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &buildRet);
	if (!buildRet)
	{
		glGetShaderInfoLog(shader, 512, NULL, buildInfo);
		LOG(buildInfo);
		throw -1;
	}
	return shader;
}

void ShaderManager::CreateShaderProgram(GLint vertexShade, GLint fragmentShaderr)
{

	int buildRet;
	char buildInfo[512];
	if (vertexShade <= 0 || fragmentShaderr<= 0)
	{
		LOG("CreateShaderProgram err");
		throw - 1;
	}
	ID = glCreateProgram();
	glAttachShader(ID, vertexShade);
	glAttachShader(ID, fragmentShaderr);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &buildRet);
	if (!buildRet)
	{
		glGetProgramInfoLog(ID, 512, NULL, buildInfo);
		LOG(buildInfo);
		throw - 1;
	}

	glDeleteShader(vertexShade);
	glDeleteShader(fragmentShaderr);
}
