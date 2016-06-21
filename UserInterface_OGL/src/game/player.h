#pragma once
#include <common.h>
#include "graphics/entities/entity.h"
#include "platform/platform.h"
#include "system/log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "system/memory.h"

namespace ho {
namespace game {

	class HO_API Player : public graphics::Entity
	{
	private:
		int m_PlayerID;
		glm::vec3 angle_vector;
		float force;
	public:

		Player(int id, graphics::Quad2D* quad, graphics::Texture* texture, float force, int num_rows, int tex_index)
			: Entity(quad, texture, num_rows, tex_index), force(force), m_PlayerID(id)
		{
			glm::vec3 v = glm::normalize(glm::vec3(-3, 1, 0));
			angle_vector = glm::vec3(m_Transform.m_Rotation * glm::vec4(v, 1));
		}

		void SetAngle()
		{
			glm::vec3 v = glm::normalize(glm::vec3(-3, 1, 0));
			angle_vector = glm::vec3(m_Transform.m_Rotation * glm::vec4(v, 1));
		}

		inline void IncForce(float f) { force += f; }
		inline int GetID() { return m_PlayerID; }
		inline glm::vec3 GetAngleVector() { return angle_vector; }
		inline float GetForce() { return force; }
		inline void SetForce(float force) { this->force = force; }
	};

}}