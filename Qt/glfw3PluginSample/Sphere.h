#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <vector>
#include <stack>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define numVAOs 1
#define numVBOs 1

class Sphere
{
public:
    Sphere();
	Sphere(unsigned prec);
	~Sphere();
	unsigned getNumVertices();
	unsigned getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec2> getTexCoords();
	void setupVerts();
    void Render(glm::mat4 camera, glm::mat4 scenePerspective);  // Render code
    void setShader(GLuint shaderProgram);                       // assigning shaders
    inline void setPosition(float X, float Y, float Z) { _positionX = X; _positionY = Y; _positionZ = Z; }
    inline void setRotationX(float degrees) { _angleX = degrees; }
    inline void setRotationY(float degrees) { _angleY = degrees; }
    inline void setRotationZ(float degrees) { _angleZ = degrees; }
    inline void setScaleX(float scale) {_scaleX = scale; }
    inline void setScaleY(float scale) {_scaleY = scale; }
    inline void setScaleZ(float scale) {_scaleZ = scale; }
    inline void setScale(float scale) {_scaleX = scale; _scaleY = scale; _scaleZ = scale; }

private:
	void init(unsigned prec);
	float toRadians(float degres);

private:
	unsigned numVertices;
	unsigned numIndices;
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
    std::stack<glm::mat4> mvStack;
    int _precision = 0;                 // sphere segments precision

private:
    std::stack<glm::mat4> _mvStack;     // stack of model matrixes
    GLuint _mvLocation, _projLocation;  // var locations within shaders
    // rotating in degrees
    float _angleX = 0.0f;
    float _angleY = 0.0f;
    float _angleZ = 0.0f;
    // positioning
    float _positionX = 0.0f;
    float _positionY = 0.0f;
    float _positionZ = 0.0f;
    // scaling
    float _scaleX = 1.0f;
    float _scaleY = 1.0f;
    float _scaleZ = 1.0f;	

private: //vertex array and object buffers
	GLuint vao[numVAOs];
	GLuint vbo[numVBOs];
	GLuint aTexture = 0;
    GLuint _shaderProgram = 0;

};

#endif // SPHERE_H
