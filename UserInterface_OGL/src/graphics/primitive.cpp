#include "primitive.h"

namespace ho {
namespace graphics {

Quad2D::Quad2D(int width, int height)
{
	Vertex2D vertices[4]{
		{ glm::vec2(-width / 2.0f,  height / 2.0f) , glm::vec2(-1.0f, 1.0f), glm::vec3(1,0,0) },
		{ glm::vec2(-width / 2.0f, -height / 2.0f) , glm::vec2(-1.0f, 0.0f), glm::vec3(0,1,0) },
		{ glm::vec2(width / 2.0f,  height / 2.0f) , glm::vec2(0.0f, 1.0f), glm::vec3(0,0,1) },
		{ glm::vec2(width / 2.0f, -height / 2.0f) , glm::vec2(0.0f, 0.0f), glm::vec3(1,1,0) }
	};
	ushort indices[] = { 0,1,2,2,1,3 };

	SetupQuad(vertices, indices);
}

Quad2D::~Quad2D()
{
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	glDeleteVertexArrays(1, &this->VAO);
}

void Quad2D::SetupQuad(Vertex2D* vertices, ushort* indices)
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2D), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
		(GLvoid*)0);
	// Vertex Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
		(GLvoid*)offsetof(Vertex2D, tex_coords));
	// Vertex Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
		(GLvoid*)offsetof(Vertex2D, color));

	glBindVertexArray(0);
}

void Quad2D::Render()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

Cube3D::Cube3D(int size)
{
	Vertex3D vertices[8]{
		{ glm::vec3(-size / 2.0f,  size / 2.0f, size / 2.0f) , glm::vec2(-1.0f, 1.0f), glm::vec3(0,0,1) },
		{ glm::vec3(-size / 2.0f, -size / 2.0f, size / 2.0f) , glm::vec2(-1.0f, 0.0f), glm::vec3(0,0,1) },
		{ glm::vec3(size / 2.0f,  size / 2.0f, size / 2.0f) , glm::vec2(0.0f, 1.0f), glm::vec3(0,0,1) },
		{ glm::vec3(size / 2.0f, -size / 2.0f, size / 2.0f) , glm::vec2(0.0f, 0.0f), glm::vec3(0,0,1) },

		{ glm::vec3(-size / 2.0f,  size / 2.0f, -size / 2.0f) , glm::vec2(-1.0f, 1.0f), glm::vec3(0,0,-1) },
		{ glm::vec3(-size / 2.0f, -size / 2.0f, -size / 2.0f) , glm::vec2(-1.0f, 0.0f), glm::vec3(0,0,-1) },
		{ glm::vec3(size / 2.0f,  size / 2.0f, -size / 2.0f) , glm::vec2(0.0f, 1.0f), glm::vec3(0,0,-1) },
		{ glm::vec3(size / 2.0f, -size / 2.0f, -size / 2.0f) , glm::vec2(0.0f, 0.0f), glm::vec3(0,0,-1) }
	};

	ushort indices[] = { 
		0, 1, 2,
		2, 1, 3,
		1, 5, 3,
		3, 5, 7,
		5, 4, 7,
		7, 4, 6,
		4, 0, 2,
		2, 4, 6,
		2, 3, 6,
		6, 3, 7,
		4, 5, 0,
		0, 5, 1
	};

	SetupCube(vertices, indices);
}

Cube3D::~Cube3D(){}

void Cube3D::SetupCube(Vertex3D* vertices, ushort* indices)
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex3D), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
		(GLvoid*)0);
	// Vertex Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
		(GLvoid*)offsetof(Vertex3D, tex_coords));
	// Vertex Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
		(GLvoid*)offsetof(Vertex3D, color));

	glBindVertexArray(0);
}

void Cube3D::Render()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

}}