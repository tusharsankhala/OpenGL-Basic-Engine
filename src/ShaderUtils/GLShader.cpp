#include "GLShader.h"
#include <StringUtils.h>

#include <glad/gl.h>
#include <assert.h>


GLShader::GLShader(const std::string fileName)
	: GLShader(GLShaderTypeFromFileName(fileName.c_str()), ReadShaderFile(fileName), fileName)
{}


GLShader::GLShader(GLenum type, const std::string source, const std::string debugFileName)
	: m_type(type)
	, m_handle(glCreateShader(type))
{
	const char* shaderSource = source.c_str();
	glShaderSource(m_handle, 1, &shaderSource, nullptr);
	glCompileShader(m_handle);

	char buffer[8192];
	GLsizei length = 0;

	glGetShaderInfoLog(m_handle, sizeof(buffer), &length, buffer);

	if (length)
	{
		printf("%s (File: %s)\n", buffer, debugFileName);
		PrintShaderSource(source);
		assert(false);
	}
}

GLShader::~GLShader()
{
	glDeleteShader(m_handle);
}

void PrintProgramInfoLog(GLuint handle)
{
	char buffer[8192];
	GLsizei length = 0;
	glGetProgramInfoLog(handle, sizeof(buffer), &length, buffer);
	if (length)
	{
		printf("%s\n", buffer);
		assert(false);
	}
}

GLProgram::GLProgram(const GLShader& a)
	: m_handle(glCreateProgram())
{
	glAttachShader(m_handle, a.GetHandle());
	glLinkProgram(m_handle);
	PrintProgramInfoLog(m_handle);
}

GLProgram::GLProgram(const GLShader& a, const GLShader& b)
	: m_handle(glCreateProgram())
{
	glAttachShader(m_handle, a.GetHandle());
	glAttachShader(m_handle, b.GetHandle());
	glLinkProgram(m_handle);
	PrintProgramInfoLog(m_handle);
}


GLProgram::GLProgram(const GLShader& a, const GLShader& b, const GLShader& c)
	: m_handle(glCreateProgram())
{
	glAttachShader(m_handle, a.GetHandle());
	glAttachShader(m_handle, b.GetHandle());
	glAttachShader(m_handle, c.GetHandle());
	glLinkProgram(m_handle);
	PrintProgramInfoLog(m_handle);
}

GLProgram::GLProgram(const GLShader& a, const GLShader& b, const GLShader& c, const GLShader& d, const GLShader& e)
	: m_handle(glCreateProgram())
{
	glAttachShader(m_handle, a.GetHandle());
	glAttachShader(m_handle, b.GetHandle());
	glAttachShader(m_handle, c.GetHandle());
	glAttachShader(m_handle, d.GetHandle());
	glAttachShader(m_handle, e.GetHandle());
	glLinkProgram(m_handle);
	PrintProgramInfoLog(m_handle);
}

GLProgram::~GLProgram()
{
	glDeleteProgram(m_handle);
}

void GLProgram::UseProgram() const
{
	glUseProgram(m_handle);
}

GLenum GLShaderTypeFromFileName(const char* fileName)
{
	if (endsWith(fileName, ".vert"))
		return GL_VERTEX_SHADER;

	if (endsWith(fileName, ".frag"))
		return GL_FRAGMENT_SHADER;

	if (endsWith(fileName, ".geom"))
		return GL_GEOMETRY_SHADER;

	if (endsWith(fileName, ".tesc"))
		return GL_TESS_CONTROL_SHADER;

	if (endsWith(fileName, ".tese"))
		return GL_TESS_EVALUATION_SHADER;

	if (endsWith(fileName, ".comp"))
		return GL_COMPUTE_SHADER;

	assert(GL_FALSE);

	return 0;
}

GLBuffer::GLBuffer(GLsizeiptr size, const void* data, GLbitfield flags)
{
	glCreateBuffers(1, &m_handle);
	glNamedBufferStorage(m_handle, size, data, flags);
}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &m_handle);
}