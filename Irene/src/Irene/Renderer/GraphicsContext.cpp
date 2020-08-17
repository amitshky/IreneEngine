#include "pch.h"
#include "Irene/Renderer/GraphicsContext.h"

#include "Irene/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace irene{

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}