#include "shader_simple3d.h"
#include "window/window.h"

namespace ho {
namespace graphics {

SimpleShader3D::SimpleShader3D(std::string& filename)
	: Shader(filename)
{
	GetUniformLocations();

	float halfWidth = Window::GetCurrentWindow().GetWidth() / 2.0f;
	float halfHeight = Window::GetCurrentWindow().GetHeight() / 2.0f;
}

SimpleShader3D::~SimpleShader3D() 
{}

void SimpleShader3D::Update(Entity& e)
{
	glm::mat4 persp = glm::perspective(70.0f, 16.0f / 9, 0.1f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glUniformMatrix4fv(m_ProjLocation, 1, GL_FALSE, &persp[0][0]);
	glUniformMatrix4fv(m_ViewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_ModelLocation, 1, GL_FALSE, &e.GetTransform().GetModelMatrix()[0][0]);
}

void SimpleShader3D::GetUniformLocations()
{
	m_ProjLocation = glGetUniformLocation(m_Shader, "m_Proj");
	m_ViewLocation = glGetUniformLocation(m_Shader, "m_View");
	m_ModelLocation = glGetUniformLocation(m_Shader, "m_Model");
	m_TextureLocation = glGetUniformLocation(m_Shader, "textSampler");
}

}}