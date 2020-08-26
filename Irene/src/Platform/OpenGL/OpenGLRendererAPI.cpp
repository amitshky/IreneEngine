#include "pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace irene {

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);	// for Multisample Anti-aliasing (MSAA)
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DepthFunc(uint32_t glEnum)
	{
		glDepthFunc(glEnum);
	}

	void OpenGLRendererAPI::Draw(uint32_t count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void OpenGLRendererAPI::DrawInstanced(uint32_t first, uint32_t count, uint32_t instanceCount)
	{
		glDrawArraysInstanced(GL_TRIANGLES, first, count, instanceCount);
	}

	void OpenGLRendererAPI::Draw(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}