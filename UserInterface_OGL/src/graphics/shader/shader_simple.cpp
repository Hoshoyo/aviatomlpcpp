#include "shader_simple.h"
#include <platform/platform.h>

namespace ho {
namespace graphics {

SimpleShader::SimpleShader(std::string& filename)
	: Shader(filename)
{
	GetUniformLocations();

	float halfWidth = Window::GetCurrentWindow().GetWidth() / 2.0f;
	float halfHeight = Window::GetCurrentWindow().GetHeight() / 2.0f;

	m_OrthoProj = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -10.0f, 10.0f);

	// start not needing to handle resize
	handleResize = false;
	Window::GetCurrentWindow().SubscribeResizeEvent(&handleResize);
}

SimpleShader::~SimpleShader()
{

}

void SimpleShader::Update(Entity& e)
{
	glUniformMatrix4fv(m_ProjLocation, 1, GL_FALSE, &m_OrthoProj[0][0]);
	glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, &e.GetTransform().GetModelMatrix()[0][0]);

	glUniform1i(m_TextureSampler, 0);

	if (handleResize)
	{
		handleResize = false;

		int width = Window::GetCurrentWindow().GetWidth();
		int height = Window::GetCurrentWindow().GetHeight();
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;
		
		m_OrthoProj = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
	}
}

void SimpleShader::GetUniformLocations()
{
	m_ProjLocation = glGetUniformLocation(m_Shader, "m_Proj");
	m_TextureSampler = glGetUniformLocation(m_Shader, "textureSampler");
	m_ModelLocation = glGetUniformLocation(m_Shader, "m_Model");
}

}}