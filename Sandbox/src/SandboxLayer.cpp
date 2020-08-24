#include <GLFW/glfw3.h>
#include "SandboxLayer.h"


SandboxLayer::SandboxLayer()
	: Layer("Sandbox Layer"), m_CameraController(16.0f / 9.0f)
{
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			m_Translations[index++] = translation;
		}
	}
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	float quadVertices[] = {
		// positions		// colors
		-0.05f,  0.05f,		1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,		0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,		0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,		1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,		0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f,		0.0f, 1.0f, 1.0f
	};

	m_VA = irene::VertexArray::Create();
	m_VB = irene::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	m_VB->SetLayout({
		{irene::ShaderDataType::Float2, "a_Position"},
		{irene::ShaderDataType::Float3, "a_Color"}
	});
	m_VA->AddVertexBuffer(m_VB);

	m_Shader = irene::Shader::Create("assets/shaders/basicShader.shader");
	m_Shader->Bind();
	for (unsigned int i = 0; i < 100; i++)
	{
		m_Shader->SetFloat2("offsets[" + std::to_string(i) + "]", m_Translations[i]);
	}
	m_Shader->Unbind();
	m_VA->Unbind();
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);

	m_VA->Bind();
	m_Shader->Bind();
	irene::RenderCommand::DrawInstanced(0, 6, 100);

}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
