#include "GLUtils.h"
#include <glad/glad.h>
#include <iostream>

namespace GLUtils
{
	int CheckForOpenGLError(const char* file, int line)
	{
		// Returns 1 if an OpenGL error occurred, 0 otherwise.
		GLenum glErr;
		int retCode = 0;

		glErr = glGetError();

		while (glErr != GL_NO_ERROR)
		{
			const char* message = "";
			switch (glErr)
			{
			case GL_INVALID_ENUM:
				message = "Invalid enum";
				break;
			case GL_INVALID_VALUE:
				message = "Invalid Value";
				break;
			case GL_INVALID_OPERATION:
				message = "Invalid Operation";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				message = "Invalid Framebuffer Operation";
				break;
			case GL_OUT_OF_MEMORY:
				message = "Out Of MemoryInvalid enum";
				break;
			default:
				message = "Unknown Error";
				break;
			}

			printf_s("glError in file %s @ line %d: %s\n", file, line, message);
			retCode = 1;
			glErr = glGetError();
		}

		return retCode;
	}	
}