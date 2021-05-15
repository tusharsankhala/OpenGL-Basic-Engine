#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "Scene.h"
#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "EBOClass.h"
#include "TextureClass.h"

#include "CommonOGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    // Matrices
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;

    GLint m_modelLoc;
    GLint m_viewLoc;
    GLint m_projLoc;
    int m_colorLoc;

public:
    SceneBasic(const int width, const int height);
    ~SceneBasic();

    void InitScene();
    void Update(float t);
    void Render();
    void Resize(int, int);

};

#endif // SCENEBASIC_H
