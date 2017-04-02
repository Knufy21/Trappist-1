#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Shader
{
public:
	Shader();
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath = "");
	virtual ~Shader();

	void load(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath = "");

	bool isLoaded() const;

	void enable() const;
	void disable() const;

	GLint getUniformLocation(const GLchar *name);

	void setUniform1f(const GLchar *name, float value);
	void setUniform1f(GLint location, float value);

	void setUniform1fv(const GLchar *name, const float *value, int count);
	void setUniform1fv(GLint location, const float *value, int count);

	void setUniform1i(const GLchar *name, int value);
	void setUniform1i(GLint location, int value);

	void setUniform1iv(const GLchar *name, const int *value, int count);
	void setUniform1iv(GLint location, const int *value, int count);

	void setUniform2f(const GLchar *name, const glm::vec2& vector);
	void setUniform2f(GLint location, const glm::vec2& vector);

	void setUniform3f(const GLchar *name, const glm::vec3& vector);
	void setUniform3f(GLint location, const glm::vec3& vector);

	void setUniform4f(const GLchar *name, const glm::vec4& vector);
	void setUniform4f(GLint location, const glm::vec4& vector);

	void setUniformMat3(const GLchar *name, const glm::mat3& matrix);
	void setUniformMat3(GLint location, const glm::mat3& matrix);

	void setUniformMat3(const GLchar *name, const GLfloat *matrix);
	void setUniformMat3(GLint location, const GLfloat *matrix);

	void setUniformMat4(const GLchar *name, const glm::mat4& matrix);
	void setUniformMat4(GLint location, const glm::mat4& matrix);

	void setUniformMat4(const GLchar *name, const GLfloat *matrix);
	void setUniformMat4(GLint location, const GLfloat *matrix);

private:
	GLuint loadShader(GLenum shaderType, const GLchar *shaderPath);

	GLuint programID;
};