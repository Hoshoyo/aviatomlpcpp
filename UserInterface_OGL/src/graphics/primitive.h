#pragma once
#include <common.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "textures/texture.h"

namespace ho {
namespace graphics {

	struct HO_API Vertex2D
	{
		glm::vec2 position;
		glm::vec2 tex_coords;
		glm::vec3 color;
	};

	struct HO_API Vertex3D
	{
		glm::vec3 position;
		glm::vec2 tex_coords;
		glm::vec3 color;
	};

	class HO_API Quad2D
	{
	public:
		Quad2D(int width, int height);
		~Quad2D();
		void Render();
	private:
		GLuint VAO, VBO, EBO;

		void SetupQuad(Vertex2D* vertices, ushort* indices);
	};

	class HO_API Cube3D
	{
	public:
		Cube3D(int size);
		~Cube3D();
		void Render();
	private:
		GLuint VAO, VBO, EBO;
		void SetupCube(Vertex3D* vertices, ushort* indices);
	};

}}
