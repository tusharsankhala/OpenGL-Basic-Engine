#include "TextureClass.h"


Texture::Texture() {}

void Texture::Create(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
    m_type = textureType;
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    glGenTextures(1, &m_textureHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(textureType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);


    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_textureHandle);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &m_textureHandle);
}