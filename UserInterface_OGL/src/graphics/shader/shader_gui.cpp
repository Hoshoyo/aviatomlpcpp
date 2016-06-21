#include "shader_gui.h"
#include "../../platform/platform.h"
#include <iostream>

namespace ho {
namespace graphics {

	ShaderGUI2D::ShaderGUI2D(std::string& filename) : Shader(filename)
	{
		GetUniformLocations();

		float half_width = Window::GetCurrentWindow().GetWidth() / 2.0f;
		float half_height = Window::GetCurrentWindow().GetHeight() / 2.0f;
		ortho = glm::ortho(-half_width, half_width, -half_height, half_height);
		//ortho = glm::perspective(70.0f, 16.0f / 9, 0.1f, 100.0f) * glm::lookAt(glm::vec3(10, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

	ShaderGUI2D::~ShaderGUI2D()
	{
	}

	void ShaderGUI2D::Update()
	{
		glm::mat4 mModel = glm::mat4(1.0f);

		glUniformMatrix4fv(m_Proj_Loc, 1, GL_FALSE, &ortho[0][0]);
		glUniformMatrix4fv(m_Model_Loc, 1, GL_FALSE, &mModel[0][0]);
		glUniform1i(m_TextureSampler_Loc, 0);
	}

	void ShaderGUI2D::GetUniformLocations()
	{
		m_Proj_Loc = glGetUniformLocation(m_Shader, "mProj");
		m_Model_Loc = glGetUniformLocation(m_Shader, "mModel");
		m_TextureSampler_Loc = glGetUniformLocation(m_Shader, "tSampler");
	}

}}