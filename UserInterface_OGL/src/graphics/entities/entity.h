#pragma once
#include <common.h>
#include "transform.h"
#include "graphics/primitive.h"
#include "graphics/textures/texture.h"
#include "platform/platform.h"
#include "graphics/entities/Irenderable.h"
#include "system/log.h"

namespace ho {
namespace graphics {

#define MAX_TEXTURES 32

	class HO_API Entity : public Renderable
	{
	public:
		Entity(Quad2D* quad);
		Entity(Quad2D* quad, Texture* texture);
		Entity(Quad2D* quad, Texture* texture, int num_rows, int texture_index);
		~Entity();

		virtual void Render();
		virtual void BindTextures();
		virtual void UnbindTextures();
		
		virtual Transform& GetTransform() { return m_Transform; }

		void CalcAtlas();
		inline int GetNumRows() { return m_NumRows; }
		inline int GetTextureIndex() { return m_TextureIndex; }
		inline void SetNumRows(int nr) { m_NumRows = nr; }
		inline void SetTextureIndex(int ti) { m_TextureIndex = ti; }
		inline Quad2D* GetQuad() { return quad; }
		inline void SetTexture(Texture* t) { m_Textures[0] = t; }

		bool isTerrain;
		bool isGrass;
		bool shouldRender;
		glm::vec2 m_TextureOffset;
	protected:
		int m_NumRows;
		int m_TextureIndex;
		Transform m_Transform;
		Texture* m_Textures[MAX_TEXTURES];
		Quad2D* quad;

	private:
		// NOTE: No copy of this allowed
		Entity& operator=(const Entity& e) = delete;
		Entity(const Entity& e) = delete;
	};

}}