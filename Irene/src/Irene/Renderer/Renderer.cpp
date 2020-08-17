#include "pch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer3D.h"

namespace irene {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer3D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->m_ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", model);
		vertexArray->Bind();
		RenderCommand::Draw(vertexArray);
	}

	void Renderer::Submit(const Ref<Shader>& shader, uint32_t count, const glm::mat4& model)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->m_ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", model);
		RenderCommand::Draw(count);
	}

}