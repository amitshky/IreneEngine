#pragma once

#include "Irene/Core/Core.h"

namespace irene {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual inline uint32_t GetWidth() const = 0;
		virtual inline uint32_t GetHeight() const = 0;
		virtual inline std::string GetType() const = 0;
		virtual inline std::string GetPath() const = 0;
		virtual inline uint32_t GetRendererID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(const std::string& path, const std::string& directory, const std::string& typeName);
		static Ref<Texture2D> Create(const std::vector<std::string>& cubeFaces);
	};

}
