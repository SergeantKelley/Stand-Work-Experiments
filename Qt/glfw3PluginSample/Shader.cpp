#include "Shader.h"

using namespace utils;

Shader::Shader(std::string path) : file(path)
{
}

// Print information
void Shader::printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}
// Print information
void Shader::printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

bool Shader::checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

// read shader sources from file
std::string Shader::readFile()
{
	std::string content;
	std::ifstream fileStream(file.c_str(), std::ios::in);
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
    return content;
}
// compile & link
GLuint Shader::createShaderProgram(const char * vShader, const char * fShader)
{
    Shader vs(vShader);
    Shader fs(fShader);
    const char * vshaderSource;
    const char * fshaderSource;

    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string s1 = vs.readFile().c_str();
    vshaderSource = s1.c_str();

    std::string s2 = fs.readFile().c_str();
    fshaderSource = s2.c_str();

    glShaderSource(vshader, 1, &vshaderSource, NULL);
    glShaderSource(fshader, 1, &fshaderSource, NULL);

    glCompileShader(vshader);
    vs.printShaderLog(vshader);
    glCompileShader(fshader);
    fs.printShaderLog(fshader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vshader);
    glAttachShader(vfProgram, fshader);

    glLinkProgram(vfProgram);

    return vfProgram;
}

