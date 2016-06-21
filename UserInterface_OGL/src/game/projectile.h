#pragma once
#include <common.h>
#include "graphics/entities/entity.h"
#include "platform/platform.h"
#include "system/log.h"
#include "game/player.h"
#include <glm/glm.hpp>
#include "system/memory.h"

namespace ho {
namespace game {

	template <typename T>
	struct HO_API PhysicalBody
	{
		T velocity;
		T initial_velocity;
		T initial_position;
		PhysicalBody()
		{
		}
	};

	class HO_API Projectile : public graphics::Entity
	{
	public:
		static const double cooldown;
	private:
		int playerId;
		PhysicalBody<glm::vec3> pb;

		double lifetime;
		const double MAX_LIFE = 5.0;
		static double spawntime;

		const float gravity = -10;
		graphics::Quad2D* quad;
		game::Player* player;

	public:
		Projectile(
			game::Player* player,
			graphics::Quad2D* quad,
			graphics::Texture* texture,
			Timer& timer);

		Projectile(
			game::Player* player,
			graphics::Quad2D* quad,
			graphics::Texture* texture,
			int tex_num_rows,
			int tex_index,
			Timer& timer);
		~Projectile()
		{
		}

		static double GetLastSpawnTime() { return spawntime; }

		bool Update(Timer& timer);

		bool CollidedWith(Player* player);

		inline int GetPlayerID() { return player->GetID();	}
	};

}}