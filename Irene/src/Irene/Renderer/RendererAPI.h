#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace irene {

	class RendererAPI
	{
	public:
		void Init();
		void SetClearColor(const glm::vec4& color);
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void Clear();

		void Draw(const Ref<VertexArray>& vertexArray);	// Draw elements
		void Draw(uint32_t count);	// Draw elements
	};

}
