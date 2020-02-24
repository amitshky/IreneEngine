#pragma once

#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D(uint32_t width, uint32_t height);
	Texture2D(const std::string& path);
	~Texture2D();

	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
	inline std::string GetType() const { return m_Type; }
	inline std::string GetPath() const { return m_Path; }
	inline uint32_t GetRendererID() const { return m_RendererID; }

	inline void SetType(const std::string& type) { m_Type = type; }
	inline void SetRendererID(const uint32_t id) { m_RendererID = id; }
	inline void SetPath(const std::string& path) { m_Path = path; }

	void SetData(void* data, uint32_t size);
	void Bind(uint32_t slot = 0) const;

private:
	std::string m_Path;
	uint32_t m_Width, m_Height;
	uint32_t m_RendererID;
	GLenum m_InternalFormat, m_DataFormat;
	std::string m_Type;		// when we need to load multiple textures
};
