#ifndef MIKECRAFT_SHADER_H
#define MIKECRAFT_SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * Simple shader class for easy use of shaders
 */
class Shader
{
public:
    //The programs set ID
    int ID;
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        unsigned int vertexShader, fragmentShader;
        //Fetch vertex and fregment from files. Convert so std::string.
        std::ifstream vertFile(vertexPath), fragFile(fragmentPath);
        std::string vertString((std::istreambuf_iterator<char>(vertFile)),std::istreambuf_iterator<char>());
        std::string fragString((std::istreambuf_iterator<char>(fragFile)),std::istreambuf_iterator<char>());
        //Initialize vertex shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, reinterpret_cast<const GLchar *const *>(&vertString), NULL);
        glCompileShader(vertexShader);
        //Initialize fragment shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, reinterpret_cast<const GLchar *const *>(&fragString), NULL);
        glCompileShader(fragmentShader);
        //Create shader program and set id to ID
        ID = glCreateProgram();
        //Attach the compiled shader object to the ID
        glAttachShader(ID, fragmentShader);
        glAttachShader(ID, vertexShader);
        //Link all attached shaders to one final shader program.
        glLinkProgram(ID);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }
};
#endif //MIKECRAFT_SHADER_H
