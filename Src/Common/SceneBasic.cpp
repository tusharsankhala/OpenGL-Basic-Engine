#include "Scenebasic.h"


#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

#include "../Utils/GLUtils.h"

SceneBasic::SceneBasic() { }
SceneBasic::~SceneBasic()
{
    vao.Delete();
    vbo.Delete();
    shader.Delete();
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

    /////////////////// Create the VBO ////////////////////
    GLfloat positionData[] = {
           -0.8f, -0.8f, 0.0f,
            1.0f, 0.0f, 0.0f,

            0.8f, -0.8f, 0.0f,
            0.0f, 1.0f, 0.0f,

            0.8f,  0.8f, 0.0f,
            0.0f, 0.0f, 1.0f,

            -0.8f, 0.8f, 0.0f,
            1.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
          0, 1, 2,
          2, 3, 0,
    };

    // Create and populate the buffer objects
    vbo.Create(positionData, sizeof(positionData));
    
    // Index buffer.
    unsigned int  iboHandle;
    glGenBuffers(1, &iboHandle);

    // Create and set-up the vertex array object
    vao.Create();
    vao.Bind();

    vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (void*)0);
    vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    vao.Unbind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    vbo.Unbind();
}

/*
void SceneBasic::LinkProgram(GLint vertShader, GLint fragShader)
{
    m_colorLoc = glGetUniformLocation(m_programHandle, "u_Color");
}
*/

void SceneBasic::Update(float t)
{
    //float r = sin(t * 10.0f);
    //glUniform4f(m_colorLoc, r, 0.0f, 0.0f, 1.0f);

    //std::cout << "r: " << r << '\n';
}

void SceneBasic::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    vao.Bind();
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    GLUtils::CheckForOpenGLError(__FILE__, __LINE__);

    vao.Unbind();
}

void SceneBasic::Resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}
