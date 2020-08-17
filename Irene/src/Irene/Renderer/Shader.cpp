#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace irene {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(filepath);
		}
		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
