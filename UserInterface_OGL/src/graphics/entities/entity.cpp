#include "entity.h"

namespace ho {
namespace graphics {

Entity::Entity(Quad2D* quad)
	: Entity(quad, nullptr, 1, 0)
{
	isTerrain = false;
	isGrass = false;
	shouldRender = true;
}

Entity::Entity(Quad2D* quad, Texture* texture)
	: quad(quad), m_Textures {}, m_NumRows(1), m_TextureIndex(0), isTerrain(false), isGrass(false)
{
	m_Textures[0] = texture;
	CalcAtlas();
	shouldRender = true;
}

Entity::Entity(Quad2D* quad, Texture* texture, int num_rows, int texture_index)
	: quad(quad), m_Textures{}, m_NumRows(num_rows), m_TextureIndex(texture_index), isTerrain(false), isGrass(false)
{
	m_Textures[0] = texture;
	CalcAtlas();
	shouldRender = true;
}

Entity::~Entity()
{
}

void Entity::CalcAtlas()
{
	int column = (int)m_TextureIndex % (int)m_NumRows;
	m_TextureOffset.x = (float)column / (float)m_NumRows;
	int row = (int)m_TextureIndex / (int)m_NumRows;
	m_TextureOffset.y = (float)row / (float)m_NumRows;
}


void Entity::Render()
{
	if(quad && shouldRender)
		quad->Render();
}

void Entity::BindTextures()
{
	for (int i = 0; m_Textures[i] != nullptr; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i]->GetTextureID());
	}
}

void Entity::UnbindTextures()
{
	for (int i = 0; m_Textures[i] != nullptr; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

}}