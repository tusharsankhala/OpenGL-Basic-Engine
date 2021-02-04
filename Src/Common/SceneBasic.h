#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "Scene.h"

#include <glad/glad.h>

#include <string>

class SceneBasic : public Scene
{
public:

    void InitScene() override;
	void Update(float t)override;
	void Render() override;
	void Resize(int, int) override;

private:
	GLuint m_vaoHandle;
	GLuint m_programHandle;

	void LinkProgram(GLint vertShader, GLint fragShader);
	void CompileShaderProgram();
	void WriteShaderBinary();
	void LoadShaderBinary(GLint);
	void LoadSpirvShader();

	std::string GetShaderInfoLog(GLuint shader);
	std::string GetProgramInfoLog(GLuint program);
};

#endif