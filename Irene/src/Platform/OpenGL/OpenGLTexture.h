#pragma once

#include "Irene/Renderer/Texture.h"

#include <glad/glad.h>

namespace irene {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(const std::string& path, const std::string& directory, const std::string& typeName);
		OpenGLTexture2D(const std::vector<std::string>& cubeFaces); // for cubemaps
		virtual ~OpenGLTexture2D();

		virtual inline uint32_t GetWidth() const override { return m_Width; }
		virtual inline uint32_t GetHeight() const override { return m_Height; }
		virtual inline std::string GetType() const override { return m_Type; }
		virtual inline std::string GetPath() const override { return m_Path; }
		virtual inline uint32_t GetRendererID() const { return m_RendererID; }

		virtual void SetData(void* data, uint32_t size) override;
		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;

		std::string m_Type = "N/A";		// when we need to load multiple textures
	};

}
