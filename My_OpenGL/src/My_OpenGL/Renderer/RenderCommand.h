#pragma once

#include "RendererAPI.h"

namespace myo {

	class RenderCommand 
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void Draw(const Ref<VertexArray>& vertexArray) // no bind vertex array
		{
			s_RendererAPI->Draw(vertexArray);
		}

		inline static void Draw(uint32_t count) // no bind vertex array
		{
			s_RendererAPI->Draw(count);
		}

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}
