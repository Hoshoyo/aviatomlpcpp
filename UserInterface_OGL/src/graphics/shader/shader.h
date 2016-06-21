#pragma once
#include <common.h>
#include "graphics/entities/entity.h"

#include <GL/glew.h>

namespace ho {
namespace graphics {

	class HO_API Shader
	{
	public:
		Shader(std::string& filename);
		virtual ~Shader();

		virtual void UseShader() const;
		virtual void StopShader() const;

		virtual void Update() = 0;
		virtual void Update(Entity&) = 0;

		void ActivateAlphaBlend() const;
		void DeactivateAlphaBlend() const;

	private:
		virtual void GetUniformLocations() = 0;
		GLuint LoadShader(const char* filename, GLuint shaderProgram) const;

	protected:
		GLuint m_Shader;

	public:
		inline GLuint GetShader() const { return m_Shader; }
	};

}}