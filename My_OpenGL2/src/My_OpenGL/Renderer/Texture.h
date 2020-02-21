#pragma once

#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D(uint32_t width, uint32_t height);
	Texture2D(const std::string& path);
	~Texture2D();

	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }

	void SetData(void* data, uint32_t size);
	void Bind(uint32_t slot = 0) const;

private:
	std::string m_Path;
	uint32_t m_Width, m_Height;
	uint32_t m_RendererID;
	GLenum m_InternalFormat, m_DataFormat;
};
