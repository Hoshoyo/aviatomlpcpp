#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "texture.h"
#include "system/memory.h"
#include "system/log.h"

namespace ho {
namespace graphics {

Texture::Texture(int width, int height)
	: m_Width(width), m_Height(height)
{
	int size = width * height;

	data = honew uint[size * sizeof(uint)];

	uint c = 0xffffffff;

	for (uint i = 0; i < height; i++)
	{
		for (uint j = 0; j < width; j++)
		{
			if (i % 10 == 0)
				c -= 0x000000ff;
			SetData(j, i, c);
		}
	}

	GenGLTextures(data);
}

Texture::Texture(std::string& filename)
{
	const int nChannels = 4;
	stbi_set_flip_vertically_on_load(1);
	data = (uint*)stbi_load(filename.c_str(), &m_Width, &m_Height, &m_Channels, nChannels);

	GenGLTextures(data);
}

int Texture::GenGLTextures(uint* data)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	return m_TextureID;
}

Texture::~Texture()
{
	hodelete data;
}

void Texture::SetData(int x, int y, uint color)
{
	if (m_Width <= x || m_Height <= y)
		log::fatal("Tried to access texture index: (", x, ", ", y,") which is out of range!");

	data[(y * m_Width) + x] = color;
}

void Texture::FlushData()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

}}
