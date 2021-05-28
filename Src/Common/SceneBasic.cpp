#include "Scenebasic.h"



#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

#include <stb_image.h>

#include "../Utils/GLUtils.h"

SceneBasic::SceneBasic(const int width, const int height) : model(glm::mat4(1.0f)),
                                                            view(glm::mat4(1.0f)),
                                                            proj(glm::mat4(1.0f))
{
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
}

SceneBasic::~SceneBasic()
{
    vao.Delete();
    vbo.Delete();
    shader.Delete();
    m_texture.Delete();
}

void SceneBasic::InitScene()
{
    // **************************************************************************************
    // Choose one of the following options for the shader program.
    //  1)  Compile the shader program normally
    //  2)  Load a binary (pre-compiled) shader program.  (file: "shader/program.bin")
    //  3)  Load a SPIR-V shader program. (files: "shader/vert.spv" and "shader/frag.spv")
    //
    // Optionally, you may attempt to write out the shader program binary using the function
    // writeShaderBinary().
    // **************************************************************************************

    // (1) Use this to load and compile the shader program.
    shader.Load("../Shaders/Basic.vert", "../Shaders/basic.frag");
    shader.Activate();

    // Setup transformation Matrix.
    m_modelLoc = shader.GetUniformLocation("model");
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    m_viewLoc = shader.GetUniformLocation("view");
    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    m_projLoc = shader.GetUniformLocation("proj");
    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, glm::value_ptr(proj));



    /////////////////// Create the VBO ////////////////////
    GLfloat positionData[] = {
        
       -0.5f, 0.0f, -0.5f,      1.0f, 0.0f, 0.0f,       0.0f, 0.0f,

       -0.5f, 0.0f, -0.5f,      1.0f, 1.0f, 0.0f,       5.0f, 0.0f,

        0.5f, 0.0f, -0.5f,      0.0f, 1.0f, 0.0f,       0.0f, 0.0f,

        0.5f, 0.0f, 0.5f,       0.0f, 0.0f, 1.0f,       5.0f, 0.0f,  

        0.0f, 0.8f, 0.0f,       1.0f, 1.0f, 1.0f,       2.5f, 5.0f,
    };

    m_indexBuffer.insert(std::end(m_indexBuffer), { 0, 1, 2,
                                                    0, 2, 3,
                                                    0, 1, 4,
                                                    1, 2, 4,
                                                    2, 3, 4,
                                                    3, 0, 4,
        });

   
    // Create and populate the buffer objects
    vbo.Create(positionData, sizeof(positionData));

    // Index buffer.
    ebo.Create();

    // Create and set-up the vertex array object
    vao.Create();
    vao.Bind();

    vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)0);
    vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));

    ebo.Bind();
    ebo.LinkAttributes(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer.size() * sizeof(unsigned int), m_indexBuffer.data(), GL_STATIC_DRAW);

    vao.Unbind();
    ebo.Unbind();

    vbo.Unbind();

    // Generating texture buffer
    m_texture.Create("../Resources/Textures/UVChecker.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    GLuint texUnit0 = shader.GetUniformLocation("tex0");
    glUniform1i(texUnit0, 0);

    m_texture.Bind();
}

/*
void SceneBasic::LinkProgram(GLint vertShader, GLint fragShader)
{
    m_colorLoc = glGetUniformLocation(m_programHandle, "u_Color");
}
*/

void SceneBasic::Update(float t)
{
    float r = t * 30.0f;
    model = glm::rotate(model, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void SceneBasic::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao.Bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    GLUtils::CheckForOpenGLError(__FILE__, __LINE__);

    vao.Unbind();
}

void SceneBasic::Resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}