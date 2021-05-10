#ifndef EBOCLASS_H
#define EBOCLASS_H

#include "CommonOGL.h"

class EBO
{
public:
	EBO();

	void Create();
	void LinkAttributes(GLenum target, GLsizeiptr size, GLuint* indices, GLenum usage);
	void Bind();
	void Unbind();

private:
	// Index buffer.
	unsigned int m_eboHandle;
};

#endif
