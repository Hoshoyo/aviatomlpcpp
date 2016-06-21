#pragma once
#include <common.h>
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ho {
	namespace graphics {
		class HO_API ShaderGUI2D : public Shader
		{
		public:
			ShaderGUI2D(std::string& filename);
			virtual ~ShaderGUI2D();
			virtual void Update();
			virtual void GetUniformLocations();
		private:
			GLuint m_Proj_Loc;
			GLuint m_Model_Loc;
			GLuint m_TextureSampler_Loc;

			glm::mat4 ortho;
		};
	}
}
