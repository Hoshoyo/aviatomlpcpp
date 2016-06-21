#pragma once
#include <common.h>
#include "graphics/layers/layer.h"
#include "graphics/primitive.h"
#include "graphics/textures/texture.h"
#include "graphics/entities/entity.h"
#include "graphics/entities/line.h"
#include "game/player.h"
#include "game/projectile.h"
#include "game/game.h"

namespace ho {
namespace graphics {

	class HO_API Layer2D : public Layer
	{
	public:
		Layer2D(game::Game* game);
		virtual ~Layer2D();
		virtual void Render();
		virtual void Update();

		void RandomizePlayersAttribs();
		int winner;
	private:
		bool Collided(game::Projectile* projectile, std::vector<Entity*>& entities, bool shoulddelete);
		Timer timer;
		game::Player* m_Player1;
		game::Player* m_Player2;
		Quad2D* m_CannonBall;
		game::Game* game;
		Line* m_P1_Line;
		Line* m_P2_Line;
	private:
		std::vector<Quad2D*> quads;
		std::vector<Quad2D*> map_quads;
		std::vector<Entity*> entities;
		std::vector<game::Projectile*> projectiles;
		std::vector<Texture*> textures;
	};

}}