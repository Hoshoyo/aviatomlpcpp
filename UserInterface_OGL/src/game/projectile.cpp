#include "projectile.h"

namespace ho {
namespace game {

	const double Projectile::cooldown = 1.0;
	double Projectile::spawntime = 0.0;

	Projectile::Projectile(
		game::Player* player,
		graphics::Quad2D* quad,
		graphics::Texture* texture,
		Timer& timer)
		: Entity(quad, texture),
		player(player),
		pb(PhysicalBody<glm::vec3>())
	{
		spawntime = timer.GetTime();
		playerId = player->GetID();
		glm::vec3 startPos = player->GetTransform().GetPosition() + (player->GetAngleVector() * 20.0f);
		this->m_Transform.SetPosition(startPos);
		lifetime = timer.GetTime();
		pb.initial_velocity = player->GetAngleVector();
		pb.initial_velocity *= player->GetForce();
	}

	Projectile::Projectile(
		game::Player* player,
		graphics::Quad2D* quad,
		graphics::Texture* texture,
		int tex_num_rows,
		int tex_index,
		Timer& timer)
		: Entity(quad, texture, tex_num_rows, tex_index),
		player(player),
		pb(PhysicalBody<glm::vec3>())
	{
		spawntime = timer.GetTime();
		playerId = player->GetID();

		glm::vec3 startPos = player->GetTransform().GetPosition() + (player->GetAngleVector() * 20.0f);
		this->m_Transform.SetPosition(startPos);
		lifetime = timer.GetTime();
		pb.initial_velocity = player->GetAngleVector();
		pb.initial_velocity *= player->GetForce();
	}

	bool Projectile::Update(Timer& timer)
	{
		double life = timer.GetTime() - lifetime;

		glm::vec3 pos = this->m_Transform.GetPosition();

		pos.y += pb.initial_velocity.y + 0.5f * gravity * (float)life * (float)life;
		pos.x += pb.initial_velocity.x + 0.5f * (float)life * (float)life;

		m_Transform.SetPosition(pos);
		pb.velocity.y = gravity * (float)life;

		if (life >= MAX_LIFE)
			return true;

		return false;
	}

	bool Projectile::CollidedWith(Player* player)
	{
		glm::vec3 e_pos = player->GetTransform().GetPosition();
		glm::vec3 p_pos = this->GetTransform().GetPosition();
		if (glm::length(e_pos - p_pos) <= 25.0f)
		{
			return true;
		}
		return false;
	}
}}
