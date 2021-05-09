#ifndef VBOCLASS_H
#define VBOCLASS_H

#include "CommonOGL.h"

class VBO
{
public:
	VBO();

	void Create(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint vboHandle;
};

#endif
