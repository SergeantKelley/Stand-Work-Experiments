#ifndef PYRAMID_H
#define PYRAMID_H

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

class Pyramid
{
public:
    Pyramid();

    unsigned getNumVertices();
    unsigned getNumIndices();
    std::vector<int> getIndices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec3> getNormals();
    std::vector<glm::vec2> getTexCoords();
    void setupVerts();
    void Render(glm::mat4 camera, glm::mat4 scenePerspective);
    void setShader(GLuint shaderProgram);
    void setPosition(float X, float Y, float Z);
    void setRotationX(float degrees);
    void setRotationY(float degrees);
    void setRotationZ(float degrees);
    inline void setScaleX(float scale) {_scaleX = scale; }
    inline void setScaleY(float scale) {_scaleY = scale; }
    inline void setScaleZ(float scale) {_scaleZ = scale; }
    inline void setScale(float scale) {_scaleX = scale; _scaleY = scale; _scaleZ = scale; }

private:
    void init(unsigned prec);

private:
    unsigned numVertices;
    unsigned numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

private:
    std::stack<glm::mat4> _mvStack;
    GLuint _mvLocation, _projLocation;
    // rotating
    float _angleX = 0.0f;
    float _angleY = 0.0f;
    float _angleZ = 0.0f;
    // positioinig
    float _positionX = 0.0f;
    float _positionY = 0.0f;
    float _positionZ = 0.0f;
    // scaling
    float _scaleX = 1.0f;
    float _scaleY = 1.0f;
    float _scaleZ = 1.0f;

private:
    // buffers to allocate in memory
    GLuint vao[numVAOs];
    GLuint vbo[numVBOs];
    // shader program address
    GLuint _shaderProgram = 0;
};

#endif // PYRAMID_H
