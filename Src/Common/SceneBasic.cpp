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
    glDeleteVertexArrays(1, &m_vaoHandle);
    glDeleteBuffers(2, vboHandles);
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
    float positionData[] = {
           -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.8f,  0.8f, 0.0f,
            -0.8f, 0.8f, 0.0f,
    };

    unsigned int indices[] = {
          0, 1, 2,
          2, 3, 0,
    };

    float colorData[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f,
    };

    // Create and populate the buffer objects
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    // Index buffer.
    unsigned int  iboHandle;
    glGenBuffers(1, &iboHandle);
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), colorData, GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &m_vaoHandle);
    glBindVertexArray(m_vaoHandle);

    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

    glBindVertexArray(m_vaoHandle);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    GLUtils::CheckForOpenGLError(__FILE__, __LINE__);

    glBindVertexArray(0);
}

void SceneBasic::Resize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}
