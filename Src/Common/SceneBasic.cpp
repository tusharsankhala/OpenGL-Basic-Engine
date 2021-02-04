#include "SceneBasic.h"

#include <iostream>
#include <fstream>
#include <sstream>

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
    CompileShaderProgram();

    /////////////////// Create the VBO ////////////////////
    float positionData[] = {
          -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f,  0.8f, 0.0f };

    float colorData[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f };

    // Create and populate the buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

    // Create and set-up the vertex array object.
    glGenVertexArrays(1, &m_vaoHandle);
    glBindVertexArray(m_vaoHandle);

    glEnableVertexAttribArray(0);       // Vertex Position.
    glEnableVertexAttribArray(1);       // Vertex Color.

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    glBindVertexArray(0);
}

void SceneBasic::Update(float t)
{

}

void SceneBasic::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void SceneBasic::Resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, width, height);
}

void SceneBasic::CompileShaderProgram()
{
    std::cout << "Compiling Shader Program" << std::endl;

    //////////////////////////////////////////////////////
    /////////// Vertex shader //////////////////////////
    //////////////////////////////////////////////////////

    // Loading the contents of the file.
    std::ifstream vertFile("../shaders/Basic.vert");
    if (!vertFile)
    {
        std::cerr << "Error opening vertex shader File" << '\n';
        return;
    }

    std::stringstream code;
    code << vertFile.rdbuf();
    vertFile.close();
    std::string codeStr(code.str());

    // Create the shader Object.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (0 == vertexShader)
    {
        std::cerr << "Error creating vertex shader" << '\n';
        return;
    }

    // Load the source code into the shader object
    const GLchar* codeArray[] = { codeStr.c_str() };
    glShaderSource(vertexShader, 1, codeArray, NULL);

    // Compile the shader.
    glCompileShader(vertexShader);

    // Check Compilation status.
    GLint result;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        std::cerr << "Vertex Shader compilation failed" << '\n';
        std::cerr << GetShaderInfoLog(vertexShader) << '\n';
        return;
    }


    //////////////////////////////////////////////////////
    /////////// Fragment shader //////////////////////////
    //////////////////////////////////////////////////////

    // Loading the contents of the file.
    std::ifstream fragFile("../shaders/Basic.frag");
    if (!fragFile)
    {
        std::cerr << "Error opening fragment shader File" << '\n';
        return;
    }

    std::stringstream fragCode;
    fragCode << fragFile.rdbuf();
    fragFile.close();
    codeStr = fragCode.str();

    // Create the shader Object.
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (0 == fragShader)
    {
        std::cerr << "Error creating fragment shader" << '\n';
        return;
    }

    // Load the source code into the shader object
    codeArray[0] = { codeStr.c_str() };
    glShaderSource(fragShader, 1, codeArray, NULL);

    // Compile the shader.
    glCompileShader(fragShader);

    // Check Compilation status.
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        std::cerr << "Fragment Shader compilation failed" << '\n';
        std::cerr << GetShaderInfoLog(fragShader) << '\n';
        return;
    }

    // Linking program.
    LinkProgram(vertexShader, fragShader);
}

void SceneBasic::LinkProgram(GLint vertShader, GLint fragShader)
{
    // Create the program object.
    m_programHandle = glCreateProgram();
    if (0 == m_programHandle)
    {
        std::cerr << "Error creating program" << '\n';
        return;
    }

    // Attach the shader.
    glAttachShader(m_programHandle, vertShader);
    glAttachShader(m_programHandle, fragShader);

    // Link the program.
    glLinkProgram(m_programHandle);

    // Check for successfull linking.
    GLint status;
    glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        std::cerr << "Failed to link the Program" << '\n';
        std::cerr << GetProgramInfoLog(m_programHandle) << '\n';
        return;
    }

    // Cleanup shader Object.
    glDetachShader(m_programHandle, vertShader);
    glDetachShader(m_programHandle, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glUseProgram(m_programHandle);
}

void SceneBasic::WriteShaderBinary()
{

}

void SceneBasic::LoadShaderBinary(GLint)
{

}

void SceneBasic::LoadSpirvShader()
{

}

std::string SceneBasic::GetShaderInfoLog(GLuint shader)
{
    GLint logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

    std::string log;
    if (logLen > 0)
    {
        log.resize(logLen, ' ');
        GLsizei written;
        glGetShaderInfoLog(shader, logLen, &written, &log[0]);
    }

    return log;
}

std::string SceneBasic::GetProgramInfoLog(GLuint program)
{
    GLint logLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);

    std::string log;
    if (logLen > 0)
    {
        log.resize(logLen, ' ');
        GLsizei written;
        glGetProgramInfoLog(program, logLen, &written, &log[0]);
    }

    return log;
}


