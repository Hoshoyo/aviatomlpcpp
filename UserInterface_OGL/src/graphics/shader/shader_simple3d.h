#pragma once
#include "shader.h"
#include "graphics/entities/entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ho {
namespace graphics {

		class HO_API SimpleShader3D : public Shader
		{
		public:
			SimpleShader3D(std::string& filename);
			virtual ~SimpleShader3D();
			virtual void Update(Entity& e);
			virtual void Update() {}

		private:
			virtual void GetUniformLocations();

			GLuint m_ProjLocation;
			GLuint m_ViewLocation;
			GLuint m_ModelLocation;
			GLuint m_TextureLocation;
			glm::mat4 m_PerspProj;
		};

}}