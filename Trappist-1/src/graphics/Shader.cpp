#include <Trappist-1\graphics\Shader.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <Trappist-1\util\DebugLog.hpp>

Shader::Shader()
	: programID(0)
{  }

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath)
	: programID(0)
{
	load(vertexPath, fragmentPath, geometryPath);
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::load(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath)
{
	if (glIsProgram(programID) == GL_TRUE)
		glDeleteProgram(programID);

	GLuint vertexShaderID, fragmentShaderID, geometryShaderID;

	programID = glCreateProgram();
	vertexShaderID = loadShader(GL_VERTEX_SHADER, vertexPath);
	glAttachShader(programID, vertexShaderID);
	if (geometryPath != "")
	{
		geometryShaderID = loadShader(GL_GEOMETRY_SHADER, geometryPath);
		glAttachShader(programID, geometryShaderID);
	}
	fragmentShaderID = loadShader(GL_FRAGMENT_SHADER, fragmentPath);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check Link-Status
	GLint linkSuccess;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength];
		GLsizei infoLogSize;
		glGetProgramInfoLog(programID, infoLogLength, &infoLogSize, infoLog);
		std::cout << infoLog << std::endl;

		delete[] infoLog;
	}

	glValidateProgram(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	if (geometryPath != "")
		glDeleteShader(geometryShaderID);
}

bool Shader::isLoaded() const
{
	return glIsProgram(programID) == GL_TRUE;
}

void Shader::enable() const
{
	glUseProgram(programID);
}

void Shader::disable() const
{
	glUseProgram(0);
}

GLint Shader::getUniformLocation(const GLchar *name)
{
	return glGetUniformLocation(programID, name);
}

void Shader::setUniform1f(const GLchar *name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1f(GLint location, float value)
{
	glUniform1f(location, value);
}

void Shader::setUniform1fv(const GLchar *name, const float *value, int count)
{
	glUniform1fv(getUniformLocation(name), count, value);
}

void Shader::setUniform1fv(GLint location, const float *value, int count)
{
	glUniform1fv(location, count, value);
}

void Shader::setUniform1i(const GLchar *name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1i(GLint location, int value)
{
	glUniform1i(location, value);
}

void Shader::setUniform1iv(const GLchar *name, const int *value, int count)
{
	glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::setUniform1iv(GLint location, const int *value, int count)
{
	glUniform1iv(location, count, value);
}

void Shader::setUniform2f(const GLchar *name, const glm::vec2 &vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform2f(GLint location, const glm::vec2 &vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void Shader::setUniform3f(const GLchar *name, const glm::vec3 &vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform3f(GLint location, const glm::vec3 &vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar *name, const glm::vec4 &vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniform4f(GLint location, const glm::vec4 &vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat3(const GLchar *name, const glm::mat3 &matrix)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat3(GLint location, const glm::mat3 &matrix)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat3(const GLchar *name, const GLfloat *matrix)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, matrix);
}

void Shader::setUniformMat3(GLint location, const GLfloat *matrix)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, matrix);
}

void Shader::setUniformMat4(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat4(GLint location, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformMat4(const GLchar *name, const GLfloat *matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix);
}

void Shader::setUniformMat4(GLint location, const GLfloat *matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

GLuint Shader::loadShader(GLenum shaderType, const GLchar *shaderPath)
{
	// Read shader code
	std::ifstream shaderFile(shaderPath);
	ERR_IF(!shaderFile.good(), "Failed to open shader file '" << shaderPath << "'");

	// Process shader code
	std::string shaderCode(std::istreambuf_iterator<char>(shaderFile), (std::istreambuf_iterator<char>()));
	const GLchar *shaderCodeAdapter = shaderCode.c_str();

	// Create and compile shader
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCodeAdapter, 0);
	glCompileShader(shaderID);

	// Check Compile-Status
	GLint compileSuccess;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength];
		GLsizei infoLogSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &infoLogSize, infoLog);
		std::cout << infoLog << std::endl;

		delete[] infoLog;
	}

	return shaderID;
}