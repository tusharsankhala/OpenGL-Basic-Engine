#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include "CommonOGL.h"
#include <string>

class Shader
{
public:
	Shader() {}
	void Load(const std::string& vertFilePath, const std::string& fragFilePath);

	std::string GetShaderInfoLog(GLuint shader);
	std::string GetProgramInfoLog(GLuint program);

	void Activate();
	void Delete();

private:
	GLuint m_programHandle;
};

#endif

