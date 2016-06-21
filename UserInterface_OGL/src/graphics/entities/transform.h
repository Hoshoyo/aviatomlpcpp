#pragma once
#include <common.h>
#include <glm/glm.hpp>

namespace ho {
namespace graphics {

	class HO_API Transform
	{
	public:
		Transform();
		Transform(glm::vec3& position, glm::vec3& scale);
		~Transform();

		void MoveTowards(glm::vec3& to, float amount);
		void ScaleBy(glm::vec3& scaleFactor);
		void RotateAround(glm::vec3& axis, float amt);
		void SetPosition(glm::vec3& pos);
		void SetScale(glm::vec3& scale);

		inline glm::mat4& GetModelMatrix() { return m_Model; }
		inline glm::vec3 GetPosition() { return m_PositionVector; }
		glm::mat4 m_Rotation;
	private:
		inline void UpdateModel();

		glm::mat4 m_Position;
		glm::mat4 m_Scale;

		glm::vec3 m_PositionVector;
		
		glm::mat4 m_Model;
	};

}}