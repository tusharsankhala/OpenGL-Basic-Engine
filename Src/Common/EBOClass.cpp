#include "EBOClass.h"

EBO::EBO()
{
}


void EBO::Create()
{
	glGenBuffers(1, &m_eboHandle);
}

void EBO::LinkAttributes(GLenum target, GLsizeiptr size, GLuint* indices, GLenum usage)
{
	glBufferData(target, size, indices, usage);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboHandle);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}