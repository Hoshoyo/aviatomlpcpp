#include "map.h"
#include "system/log.h"
#include "graphics/primitive.h"
#include <fstream>
#include "system/memory.h"

namespace ho {
namespace game {

Map::Map(const char* filename)
{
	std::ifstream mapfile;
	mapfile.open(filename);
	if (!mapfile.is_open())
		log::fatal("File not found ", filename);

	char buffer[2048] = {};
	// Find out file size
	mapfile.seekg(0, std::ios_base::end);
	int filesize = (int)mapfile.tellg();
	if (filesize > 2048)
		log::fatal("Map size is too big");

	mapfile.seekg(0);
	mapfile.read(buffer, filesize);
	mapfile.close();
	FillMapInfo(buffer);
}

Map::~Map()
{

}

void Map::LoadGameMap(
	graphics::Entity* p1, 
	graphics::Entity* p1b,
	graphics::Entity* p2,
	graphics::Entity* p2b,
	graphics::Texture* tile,
	std::vector<graphics::Entity*>& entities, 
	std::vector<graphics::Quad2D*>& quads,
	int ww, int wh)
{
	for (int y = 0; y < this->GetHeight(); y++)
	{
		for (int x = 0; x < this->GetWidth(); x++)
		{
			if (this->GetMapInfo(x, y) == 'T' ||		// terreno meio
				this->GetMapInfo(x, y) == 'U' ||		// terreno direita
				this->GetMapInfo(x, y) == 'G' ||		// grama meio
				this->GetMapInfo(x, y) == 'H' ||		// grama direita
				this->GetMapInfo(x, y) == 'F' ||		// grama esquerda
				this->GetMapInfo(x, y) == 'D' ||		// canhao p2
				this->GetMapInfo(x, y) == 'C' ||		// canhao p1
				this->GetMapInfo(x, y) == 'S')
			{
				int tile_index = 0;
				bool is_map = true;
				const float can_yoff = 40.0f;
				const float can_xoff = 0.0f;
				const float base_xoff = 10.0f;
				const float base_yoff = 30.0f;
				bool isgrass = false;
				switch (this->GetMapInfo(x, y))
				{
				case 'U': tile_index = 0; break;
				case 'S': tile_index = 1; break;
				case 'T': tile_index = 2; break;
				case 'H': tile_index = 3; break;
				case 'F': tile_index = 4; break;
				case 'G': tile_index = 5; isgrass = true; break;
				case 'C':
					p1b->GetTransform().SetPosition(glm::vec3(
						x * tile_size - ww / 2.0f + tile_size / 2.0f - base_xoff,
						y * tile_size - wh / 2.0f + tile_size / 2.0f - base_yoff,
						3.0f));
					p1->GetTransform().SetPosition(glm::vec3(
						x * tile_size - ww / 2.0f + tile_size / 2.0f - can_xoff,
						y * tile_size - wh / 2.0f + tile_size / 2.0f - can_yoff,
						2.0f));

					is_map = false;
					break;
				case 'D':
					p2b->GetTransform().SetPosition(glm::vec3(
						x * tile_size - ww / 2.0f + tile_size / 2.0f - base_xoff,
						y * tile_size - wh / 2.0f + tile_size / 2.0f - base_yoff,
						3.0f));
					p2->GetTransform().SetPosition(glm::vec3(
						x * tile_size - ww / 2.0f + tile_size / 2.0f - can_xoff,
						y * tile_size - wh / 2.0f + tile_size / 2.0f - can_yoff,
						2.0f));

					is_map = false;
					break;
				}


				if (!is_map)
					continue;

				graphics::Quad2D* q = honew graphics::Quad2D(tile_size, tile_size);
				quads.push_back(q);
				graphics::Entity* e = honew graphics::Entity(q, tile, 3, tile_index);
				e->GetTransform().SetPosition(glm::vec3(
					x * tile_size - ww / 2.0f + tile_size / 2.0f,
					y * tile_size - wh / 2.0f + tile_size / 2.0f,
					2.0f));
				e->isTerrain = true;
				e->isGrass = isgrass;
				entities.push_back(e);
			}
		}
	}
}

void Map::FillMapInfo(char* buffer)
{
	m_Width = 0;
	m_Height = 1;

	for (int i = 0, v = 0, f = 0; buffer[i] != 0; ++i)
	{
		if (buffer[i] == '\n')
		{
			m_Height++;
			if(f == 0)
				m_Width = i;
			f++;
			continue;
		}
		map_data[v] = buffer[i];
		v++;
	}
	char* f = map_data;
}

char Map::GetMapInfo(int x, int y) 
{
	return map_data[(m_Height - y - 1) * m_Width + x];
}

}}