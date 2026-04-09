#include "Sphere.h"

Sphere::Sphere()
{
    _precision = 36;
    init(_precision);
}

Sphere::Sphere(unsigned prec)
{
    _precision = prec;
    init(_precision);
}

Sphere::~Sphere()
{

}

unsigned Sphere::getNumVertices()
{
	return numVertices;
}

unsigned Sphere::getNumIndices()
{
	return numIndices;
}

std::vector<int> Sphere::getIndices()
{
	return indices;
}

std::vector<glm::vec3> Sphere::getVertices()
{
	return vertices;
}

std::vector<glm::vec3> Sphere::getNormals()
{
	return normals;
}

std::vector<glm::vec2> Sphere::getTexCoords()
{
	return texCoords;
}

void Sphere::init(unsigned prec)
{
	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	for (unsigned i = 0; i < numVertices; i++) vertices.push_back(glm::vec3());
	for (unsigned i = 0; i < numVertices; i++) texCoords.push_back(glm::vec2());
	for (unsigned i = 0; i < numVertices; i++) normals.push_back(glm::vec3());
	for (unsigned i = 0; i < numIndices; i++) indices.push_back(0);

	for (unsigned i = 0; i <= prec; i++)
	{
		for (unsigned j = 0; j <= prec; j++)
		{
			float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
			float x = -(float)cos(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			vertices[i*(prec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i*(prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
			normals[i*(prec + 1) + j] = glm::vec3(x, y, z);
		}
	}

	for (unsigned i = 0; i < prec; i++)
	{
		for (unsigned j = 0; j < prec; j++)
		{
			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}
}

float Sphere::toRadians(float degres)
{
	return degres * 2.0f * 3.14159f / 360.0f;
}

void Sphere::setupVerts()
{
	std::vector<int> inds = getIndices();
	std::vector<glm::vec3> verts = getVertices();
	std::vector<glm::vec2> textCoords = getTexCoords();
	std::vector<glm::vec3> normals = getNormals();

	std::vector<float> pvalues;
	std::vector<float> tvalues;
	std::vector<float> nvalues;

	unsigned numIndices = getNumIndices();

	for (unsigned i = 0; i < numIndices; i++)
	{
		pvalues.push_back((verts[inds[i]]).x);
		pvalues.push_back((verts[inds[i]]).y);
		pvalues.push_back((verts[inds[i]]).z);

		tvalues.push_back((textCoords[inds[i]]).s);
		tvalues.push_back((textCoords[inds[i]]).t);

		nvalues.push_back((normals[inds[i]]).x);
		nvalues.push_back((normals[inds[i]]).y);
		nvalues.push_back((normals[inds[i]]).z);
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
    glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);
}
// Rendering
void Sphere::Render(glm::mat4 camera, glm::mat4 scenePerspective)
{
    glUseProgram(_shaderProgram);
        _mvLocation = glGetUniformLocation(_shaderProgram, "mv_matrix");
        _projLocation = glGetUniformLocation(_shaderProgram, "proj_matrix");

        _mvStack.push(camera);
        glUniformMatrix4fv(_mvLocation, 1, GL_FALSE, glm::value_ptr(_mvStack.top()));
        glUniformMatrix4fv(_projLocation, 1, GL_FALSE, glm::value_ptr(scenePerspective));

        // "The Sphere"
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, getNumIndices());

        _mvStack.pop();
        _mvStack.pop();
    glUseProgram(0);
}

void Sphere::setShader(GLuint shaderProgram)
{
	_shaderProgram = shaderProgram;
}
