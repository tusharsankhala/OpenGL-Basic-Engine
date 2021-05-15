#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H

#include "CommonOGL.h"
#include <stb_image.h>

class Texture
{
public:
	Texture();

	void Create(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);
	void Bind();
	void UnBind();
	void Delete();

private:
	GLuint m_textureHandle;
	GLenum m_type;
};

#endif
