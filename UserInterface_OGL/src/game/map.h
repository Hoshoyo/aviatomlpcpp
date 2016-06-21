#pragma once
#include <common.h>
#include "graphics/entities/entity.h"
#include "graphics/textures/texture.h"
#include <vector>

namespace ho {
namespace game {

	class HO_API Map
	{
	public:
		Map(const char* filename);
		~Map();

		const float tile_size = 50.0f;

		inline const char* GetMapData() { return map_data; }
		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }
		char GetMapInfo(int x, int y);
		void LoadGameMap(
			graphics::Entity* p1,
			graphics::Entity* p1b,
			graphics::Entity* p2,
			graphics::Entity* p2b,
			graphics::Texture* tile,
			std::vector<graphics::Entity*>& entities,
			std::vector<graphics::Quad2D*>& quads,
			int ww, int wh);
	private:
		char map_data[2048];
		int m_Width;
		int m_Height;

		void FillMapInfo(char* buffer);
	};

}}
