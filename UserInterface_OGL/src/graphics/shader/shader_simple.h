#pragma once
#include "shader.h"
#include "graphics/entities/entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ho {
namespace graphics {

	class HO_API SimpleShader : public Shader
	{
	public:
		SimpleShader(std::string& filename);
		virtual ~SimpleShader();
		virtual void Update(Entity& e);
		virtual void Update() {}

		bool handleResize;
	private:
		virtual void GetUniformLocations();

		GLuint m_ProjLocation;
		GLuint m_TextureSampler;
		GLuint m_ModelLocation;
		glm::mat4 m_OrthoProj;
	};

}}