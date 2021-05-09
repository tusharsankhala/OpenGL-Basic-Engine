#include "ShaderClass.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string ReadShaderFile(const std::string& filePath)
{
    // Load contents of file
    std::ifstream inFile(filePath);
    if (!inFile)
    {
        fprintf(stderr, "Error opening file");
        std::cout << filePath << '\n';
        exit(1);
    }

    std::stringstream code;
    code << inFile.rdbuf();
    inFile.close();

    return code.str();
}

void Shader::Load(const std::string& vertFilePath, const std::string& fragFilePath)
{
    std::cout << "Compiling shader program" << std::endl;

    std::string vertShaderSrc = ReadShaderFile(vertFilePath);
    std::string fragShaderSrc = ReadShaderFile(fragFilePath);
   
    // Create the shader object
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    if (0 == vertShader)
    {
        std::cerr << "Error creating vertex shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Load the source code into the shader object
    const GLchar* shaderSrcArray[] = { vertShaderSrc.c_str() };
    glShaderSource(vertShader, 1, shaderSrcArray, NULL);

    // Compile the shader
    glCompileShader(vertShader);

    // Check compilation status
    GLint result;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        std::cerr << "Vertex shader compilation failed!" << std::endl;
        //std::cerr << GetShaderInfoLog(vertShader) << std::endl;
        exit(EXIT_FAILURE);
    }

    //////////////////////////////////////////////////////
    /////////// Fragment shader //////////////////////////
    //////////////////////////////////////////////////////

    // Create the shader object
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (0 == fragShader)
    {
        fprintf(stderr, "Error creating fragment shader.\n");
        exit(1);
    }

    // Load the source code into the shader object
    shaderSrcArray[0] = fragShaderSrc.c_str();
    glShaderSource(fragShader, 1, shaderSrcArray, NULL);

    // Compile the shader
    glCompileShader(fragShader);

    // Check compilation status
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result)
    {
        std::cerr << "Fragment shader compilation failed!" << std::endl;
        std::cerr << GetShaderInfoLog(fragShader) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create the program object
    m_programHandle = glCreateProgram();
    if (0 == m_programHandle) {
        std::cerr << "Error creating program object." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Bind index 0 to the shader input variable "VertexPosition"
    // glBindAttribLocation(programHandle, 0, "VertexPosition");
    // Bind index 1 to the shader input variable "VertexColor"
    // glBindAttribLocation(programHandle, 1, "VertexColor");

    // Attach the shaders to the program object
    glAttachShader(m_programHandle, vertShader);
    glAttachShader(m_programHandle, fragShader);

    // Link the program
    glLinkProgram(m_programHandle);

    // Check for successful linking
    GLint status;
    glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        std::cerr << "Failed to link shader program!" << std::endl;
        std::cerr << GetProgramInfoLog(m_programHandle) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Clean up shader objects
    glDetachShader(m_programHandle, vertShader);
    glDetachShader(m_programHandle, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

std::string Shader::GetShaderInfoLog(GLuint shader)
{
    GLint logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

    std::string log;
    if (logLen > 0) {
        log.resize(logLen, ' ');
        GLsizei written;
        glGetShaderInfoLog(shader, logLen, &written, &log[0]);
    }

    return log;
}

std::string Shader::GetProgramInfoLog(GLuint program)
{
    GLint logLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);

    std::string log;
    if (logLen > 0) {
        log.resize(logLen, ' ');
        GLsizei written;
        glGetProgramInfoLog(program, logLen, &written, &log[0]);
    }
    return log;
}


void Shader::Activate()
{
    glUseProgram(m_programHandle);
}

void Shader::Delete()
{
    glUseProgram(0);
    glDeleteProgram(m_programHandle);
}