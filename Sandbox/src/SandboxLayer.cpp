#include <GLFW/glfw3.h>
#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
	: Layer("Framebuffer Test"), m_CameraController(16.0f / 9.0f)
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	float points[] = {
		-0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // top-left
		 0.5f,  0.5f,	0.0f, 1.0f, 0.0f, // top-right
		 0.5f, -0.5f,	0.0f, 0.0f, 1.0f, // bottom-right
		-0.5f, -0.5f,	1.0f, 1.0f, 0.0f  // bottom-left
	};

	m_VA = irene::VertexArray::Create();
	m_VB = irene::VertexBuffer::Create(points, sizeof(points));
	m_VB->SetLayout({
		{irene::ShaderDataType::Float2, "a_Position"},
		{irene::ShaderDataType::Float3, "a_Color"}
	});
	m_VA->AddVertexBuffer(m_VB);

	m_Shader = irene::Shader::Create("assets/shaders/geometryShader.shader");
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	irene::Renderer3D::BeginScene(m_CameraController.GetCamera());
	m_Shader->Bind();
	m_VA->Bind();
	glDrawArrays(GL_POINTS, 0, 4);

	irene::Renderer3D::EndScene();
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
