#pragma once

#include <glad/gl.h>

#include <string>

class GLShader
{
public:
	explicit GLShader(const std::string fileName);
	GLShader(GLenum type, const std::string source, const std::string debugFileName = "");
	~GLShader();

	GLenum GetType() const { return m_type; }
	GLuint GetHandle() const { return m_handle; }

private:
	GLenum m_type;
	GLuint m_handle;
};

class GLProgram
{
public:
	GLProgram(const GLShader& a);
	GLProgram(const GLShader& a, const GLShader& b);
	GLProgram(const GLShader& a, const GLShader& b, const GLShader& c);
	GLProgram(const GLShader& a, const GLShader& b, const GLShader& c, const GLShader& d, const GLShader& e);

	~GLProgram();

	void UseProgram() const;
	GLuint GetHandle() const { return m_handle; }

private:
	GLuint m_handle;
};

GLenum GLShaderTypeFromFileName(const char* fileName);

class GLBuffer
{
public:
	GLBuffer(GLsizeiptr size, const void* data, GLbitfield flags);
	~GLBuffer();

	GLuint GetHandle() { return m_handle; }

private:
	GLuint m_handle;
};