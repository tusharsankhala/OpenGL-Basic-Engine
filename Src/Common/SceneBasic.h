#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "Scene.h"

#include "CommonOGL.h"
#include <string>

class SceneBasic : public Scene
{
private:
    GLuint m_vaoHandle;
    GLuint m_programHandle;

    void LinkProgram(GLint vertShader, GLint fragShader);
    void CompileShaderProgram();
    void WriteShaderBinary();
    void LoadShaderBinary(GLint);
    //void LoadSpirvShader();

    std::string GetShaderInfoLog(GLuint shader);
    std::string GetProgramInfoLog(GLuint program);

public:
    SceneBasic();

    void InitScene();
    void Update(float t);
    void Render();
    void Resize(int, int);

};

#endif // SCENEBASIC_H
