#pragma once

#include "Irene/Renderer/RendererAPI.h"

namespace irene {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;

		virtual void Draw(const Ref<VertexArray>& vertexArray) override;	// Draw elements
		virtual void Draw(uint32_t count) override;	// Draw elements
	};

}