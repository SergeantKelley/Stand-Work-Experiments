#include "Cube.h"

Cube::Cube()
{

}

unsigned Cube::getNumVertices()
{
    // temporarily left blank
    return 0;
}

unsigned Cube::getNumIndices()
{
    // temporarily left blank
    return 0;
}

std::vector<int> Cube::getIndices()
{
    // temporarily left blank
    return std::vector<int>();
}

std::vector<glm::vec3> Cube::getVertices()
{
    // temporarily left blank
    return std::vector<glm::vec3>();
}

std::vector<glm::vec3> Cube::getNormals()
{
    // temporarily left blank
    return std::vector<glm::vec3>();
}

std::vector<glm::vec2> Cube::getTexCoords()
{
    // temporarily left blank
    return std::vector<glm::vec2>();
}
// hardcoding cube vertex positions. The size is equal to 2x2x2
void Cube::setupVerts()
{
    float vertexPositions[108] =
        {
            -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
            1.0f,  -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
            1.0f,  -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
            1.0f,  -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
            1.0f,  -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
        };

        glGenVertexArrays(1, vao);
        glBindVertexArray(vao[0]);
        glGenBuffers(numVBOs, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

// Render Code
void Cube::Render(glm::mat4 camera, glm::mat4 scenePerspective)
{
    glUseProgram(_shaderProgram);
        _mvLocation = glGetUniformLocation(_shaderProgram, "mv_matrix");
        _projLocation = glGetUniformLocation(_shaderProgram, "proj_matrix");

        _mvStack.push(camera);
        glUniformMatrix4fv(_mvLocation, 1, GL_FALSE, glm::value_ptr(_mvStack.top()));
        glUniformMatrix4fv(_projLocation, 1, GL_FALSE, glm::value_ptr(scenePerspective));

        // "The Cube"
        _mvStack.push(_mvStack.top());
        _mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(_positionX, _positionY, _positionZ));
        _mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(_scaleX, _scaleY, _scaleZ));
        _mvStack.top() *= glm::rotate(glm::mat4(1.0f), glm::radians(_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
        _mvStack.top() *= glm::rotate(glm::mat4(1.0f), glm::radians(_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
        _mvStack.top() *= glm::rotate(glm::mat4(1.0f), glm::radians(_angleZ) , glm::vec3(0.0f, 0.0f, 1.0f));
        _mvStack.push(_mvStack.top());
        glUniformMatrix4fv(_mvLocation, 1, GL_FALSE, glm::value_ptr(_mvStack.top()));

        /////////////////////////////////////////////////////////

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        _mvStack.pop();
        _mvStack.pop();
    glUseProgram(0);
}
// setup shader
void Cube::setShader(GLuint shaderProgram)
{
    _shaderProgram = shaderProgram;
}

