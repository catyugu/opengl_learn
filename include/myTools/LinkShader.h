//
// Created by kali on 10/26/24.
//

#ifndef LINKSHADER_H
#define LINKSHADER_H
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

inline char* linkShaders(const std::string &ShaderSourcePath) {

    std::ifstream vShaderFile;
    try {
        // open files
        vShaderFile.open(ShaderSourcePath);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        // convert stream into char*
        char* vertexCode = new char[vShaderStream.str().size()];
        strcpy(vertexCode, vShaderStream.str().c_str());
        vertexCode[vShaderStream.str().size()] = '\0';
        return vertexCode;
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return nullptr;
    }
}
inline GLuint UseVertexShader(const std::string& ShaderSourcePath) {
    const char* vertexShaderSource = linkShaders(ShaderSourcePath);
    if (vertexShaderSource == nullptr) {
      delete vertexShaderSource;
      return -1;
    }
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    auto success = GL_FALSE;
    auto* infoLog = new GLchar[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
      std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    return vertexShader;
}
inline GLuint UseFragmentShader(const std::string& ShaderSourcePath) {
    const char* fragmentShaderSource = linkShaders(ShaderSourcePath);
    if (fragmentShaderSource == nullptr) {
      delete fragmentShaderSource;
      return -1;
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    auto success = GL_FALSE;
    auto* infoLog = new GLchar[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
      std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    return fragmentShader;
}
inline GLuint UseGeometryShader(const std::string& ShaderSourcePath) {
    const char* geometryShaderSource = linkShaders(ShaderSourcePath);
    if (geometryShaderSource == nullptr) {
      delete geometryShaderSource;
      return -1;
    }
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryShaderSource, nullptr);
    glCompileShader(geometryShader);
    auto success = GL_FALSE;
    auto* infoLog = new GLchar[512];
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog);
      std::cout << "ERROR::GEOMETRY::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    return geometryShader;
}
#endif //LINKSHADER_H
