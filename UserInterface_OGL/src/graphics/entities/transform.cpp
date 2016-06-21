#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ho {
namespace graphics {

Transform::Transform()
	: Transform(glm::vec3(0,0,0), glm::vec3(1,1,1))
{
}

Transform::Transform(glm::vec3& position, glm::vec3& scale)
{
	m_Position	= glm::translate(glm::mat4(), position);
	m_Rotation	= glm::mat4(1.0f);
	m_Scale		= glm::scale(glm::mat4(), scale);
}

void Transform::MoveTowards(glm::vec3& to, float amount)
{
	glm::vec3 moveto = glm::normalize(to);
	moveto *= amount;
	m_Position *= glm::translate(glm::mat4(), moveto);
	m_PositionVector = glm::vec3(m_Position[3][0], m_Position[3][1], m_Position[3][2]);
	UpdateModel();
}

void Transform::RotateAround(glm::vec3& axis, float amt)
{
	m_Rotation *= glm::rotate(glm::mat4(), amt, axis);
	UpdateModel();
}

void Transform::ScaleBy(glm::vec3& scaleFactor)
{
	m_Scale *= glm::scale(glm::mat4(), scaleFactor);
	UpdateModel();
}

void Transform::SetPosition(glm::vec3& pos)
{
	m_PositionVector = pos;
	m_Position = glm::translate(glm::mat4(), pos);
	UpdateModel();
}

void Transform::SetScale(glm::vec3& scale)
{
	m_Scale = glm::scale(glm::mat4(), scale);
	UpdateModel();
}

void Transform::UpdateModel()
{
	m_Model = m_Position * m_Rotation * m_Scale;
}

Transform::~Transform()
{

}

}}