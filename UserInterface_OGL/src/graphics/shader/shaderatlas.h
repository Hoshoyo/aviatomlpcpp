#pragma once
#include "shader.h"
#include "graphics/entities/entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ho {
	namespace graphics {

		class HO_API ShaderAtlas : public Shader
		{
		public:
			ShaderAtlas(std::string& filename);
			virtual ~ShaderAtlas();
			virtual void Update(Entity& e);
			virtual void Update() {}

		private:
			virtual void GetUniformLocations();

			GLuint m_ProjLocation;
			GLuint m_TextureSampler;
			GLuint m_ModelLocation;
			GLuint m_TextureOffsetLocation;
			GLuint m_TextureNumRowsLocation;

			glm::mat4 m_OrthoProj;
		};

	}
}