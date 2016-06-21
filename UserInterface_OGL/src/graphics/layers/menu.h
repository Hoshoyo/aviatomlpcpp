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

		class HO_API Menu : public Layer
		{
		public:
			Menu();
			virtual ~Menu();
			virtual void Render();
			virtual void Update();

			bool start_game;
			bool quit_game;

			void SwitchMenuTexture(int winner);
		private:
			std::vector<Quad2D*> quads;
			std::vector<Entity*> entities;
			std::vector<Texture*> textures;

			Shader* m_Shader;

			Entity* m_BackgroundEntity;
			Entity* m_NewGame, *m_NewGameHover;
			Entity* m_Quit, *m_QuitHover;
			Texture* p1w, *p2w, *background;
		};

}}