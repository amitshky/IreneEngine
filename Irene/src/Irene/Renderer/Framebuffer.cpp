#include "pch.h"
#include "Framebuffer.h"

#include "Irene/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace irene {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(spec);
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

