#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
*  Shader utility class provides compiling, linking and logging error information
*/

namespace utils {

class Shader
{
public:
    Shader(std::string path);

public:
    void printShaderLog(GLuint shader);
    void printProgramLog(int prog);
    bool checkOpenGLError();
    std::string readFile();                                                      //
    static GLuint createShaderProgram(const char* vShader, const char* fShader); // cook shaders

private:
    std::string file;

};

}
#endif // SHADER_H
