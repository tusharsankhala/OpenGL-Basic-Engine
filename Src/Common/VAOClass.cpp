#include "VAOClass.h"

VAO::VAO()
{}

// Create and set-up the vertex array object
void VAO::Create()
{
	glGenVertexArrays(1, &m_vaoHandle);
}

void VAO::LinkAttributes(VBO vbo, GLuint layout, GLuint numComponents,
						 GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(m_vaoHandle);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &m_vaoHandle);
}