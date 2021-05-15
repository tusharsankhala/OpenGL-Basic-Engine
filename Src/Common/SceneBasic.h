#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "Scene.h"
#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "EBOClass.h"
#include "TextureClass.h"

#include "CommonOGL.h"
#include <string>

class SceneBasic : public Scene
{
private:
    GLuint m_vaoHandle;
    GLuint m_programHandle;
    GLuint vboHandles[2];
    Shader shader;
    VAO vao;
    VBO vbo;
    EBO ebo;
    Texture m_texture;

    int m_colorLoc;

public:
    SceneBasic();
    ~SceneBasic();

    void InitScene();
    void Update(float t);
    void Render();
    void Resize(int, int);

};

#endif // SCENEBASIC_H
