#include "Pyramid.h"

Pyramid::Pyramid()
{

}

unsigned Pyramid::getNumVertices()
{
 // temporarily left blank
    return 0;
}

unsigned Pyramid::getNumIndices()
{
// temporarily left blank
    return 0;
}

std::vector<int> Pyramid::getIndices()
{
// temporarily left blank
    return std::vector<int>();
}

std::vector<glm::vec3> Pyramid::getVertices()
{
// temporarily left blank
    return std::vector<glm::vec3>();
}

std::vector<glm::vec3> Pyramid::getNormals()
{
// temporarily left blank
    return std::vector<glm::vec3>();
}

std::vector<glm::vec2> Pyramid::getTexCoords()
{
// temporarily left blank
    return std::vector<glm::vec2>();
}

void Pyramid::setupVerts()
{
    float pyramidPositions[54] =
    {
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //front
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,    //right
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  //back
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //left
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, //LF
        1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f  //RR
    };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);
}

void Pyramid::Render(glm::mat4 camera, glm::mat4 scenePerspective)
{
    glUseProgram(_shaderProgram);
        _mvLocation = glGetUniformLocation(_shaderProgram, "mv_matrix");
        _projLocation = glGetUniformLocation(_shaderProgram, "proj_matrix");

        _mvStack.push(camera);
        glUniformMatrix4fv(_mvLocation, 1, GL_FALSE, glm::value_ptr(_mvStack.top()));
        glUniformMatrix4fv(_projLocation, 1, GL_FALSE, glm::value_ptr(scenePerspective));

        // "The Pyramid"
        _mvStack.push(_mvStack.top());
        _mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(_positionX, _positionY, _positionZ));
        _mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(_scaleX, _scaleY, _scaleZ));
        _mvStack.top() *= glm::rotate(glm::mat4(1.0f), glm::radians(_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
        _mvStack.top() *= glm::rotate(glm::mat4(1.0f), glm::radians(_angleY), glm::vec3(1.0f, 0.0f, 0.0f));
        _mvStack.top() *= glm::rotate(glm::mat4(1.0f), glm::radians(-_angleZ) , glm::vec3(0.0f, 0.0f, 1.0f));
        _mvStack.push(_mvStack.top());
        glUniformMatrix4fv(_mvLocation, 1, GL_FALSE, glm::value_ptr(_mvStack.top()));

        /////////////////////////////////////////////////////////
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glDrawArrays(GL_TRIANGLES, 0, 18);

        _mvStack.pop();
        _mvStack.pop();
    glUseProgram(0);
}

void Pyramid::setShader(GLuint shaderProgram)
{
    _shaderProgram = shaderProgram;
}

void Pyramid::setPosition(float X, float Y, float Z)
{
    _positionX = X;
    _positionY = Y;
    _positionZ = Z;
}

void Pyramid::setRotationX(float degrees)
{
    _angleX = degrees;
}

void Pyramid::setRotationY(float degrees)
{
    _angleY = degrees;
}

void Pyramid::setRotationZ(float degrees)
{
    _angleZ = degrees;
}

void Pyramid::init(unsigned prec)
{
    (void)(prec);
}

