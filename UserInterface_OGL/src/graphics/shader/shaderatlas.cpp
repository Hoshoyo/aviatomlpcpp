#include "shaderatlas.h"
#include <platform/platform.h>

namespace ho {
	namespace graphics {

		ShaderAtlas::ShaderAtlas(std::string& filename)
			: Shader(filename)
		{
			GetUniformLocations();

			float halfWidth = Window::GetCurrentWindow().GetWidth() / 2.0f;
			float halfHeight = Window::GetCurrentWindow().GetHeight() / 2.0f;

			m_OrthoProj = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -10.0f, 10.0f);

		}

		ShaderAtlas::~ShaderAtlas()
		{
		}

		void ShaderAtlas::Update(Entity& e)
		{
			glUniformMatrix4fv(m_ProjLocation, 1, GL_FALSE, &m_OrthoProj[0][0]);
			glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, &e.GetTransform().GetModelMatrix()[0][0]);
			glUniform2fv(m_TextureOffsetLocation, 1, &e.m_TextureOffset[0]);
			glUniform1f(m_TextureNumRowsLocation, (GLfloat)e.GetNumRows());

			glUniform1i(m_TextureSampler, 0);
		}

		void ShaderAtlas::GetUniformLocations()
		{
			m_ProjLocation = glGetUniformLocation(m_Shader, "m_Proj");
			m_TextureSampler = glGetUniformLocation(m_Shader, "textureSampler");
			m_ModelLocation = glGetUniformLocation(m_Shader, "m_Model");
			m_TextureOffsetLocation = glGetUniformLocation(m_Shader, "texture_offset");
			m_TextureNumRowsLocation = glGetUniformLocation(m_Shader, "texture_num_rows");
		}

	}
}