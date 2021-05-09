#ifndef VAOCLASS_H
#define VAOCLASS_H

#include "VBOClass.h"
#include "CommonOGL.h"

class VAO
{
public:
	VAO();

	void LinkAttributes(VBO vbo, GLuint layout, GLuint numComponents,
						GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint m_vaoHandle;
};

#endif

