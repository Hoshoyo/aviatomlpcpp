#pragma once
#include <common.h>
#include <GL/glew.h>

namespace ho {
namespace graphics {

	class HO_API Texture
	{
	public:
		Texture(int width, int height);
		Texture(std::string& filename);
		~Texture();
		GLuint GetTextureID() const	{ return m_TextureID; }

		void SetData(int x, int y, uint color);
		void FlushData();

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }
		inline int GetChannels() { return m_Channels; }
	private:
		int m_Width, m_Height, m_Channels;
		uint* data;
		GLuint m_TextureID;

		int GenGLTextures(uint* data);

		//byte* loadedImage;

	};

}}
