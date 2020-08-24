#include <GLFW/glfw3.h>
#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
	: Layer("Sandbox Layer"), m_CameraController(16.0f / 9.0f)
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	m_NanosuitShader = irene::Shader::Create("assets/shaders/NanosuitModel.shader");
	m_NanosuitModel = irene::Model::Create("assets/3DModels/nanosuit/nanosuit.obj");
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);

	irene::Renderer::BeginScene(m_CameraController.GetCamera());

	// Nanosuit model
	m_NanosuitShader->Bind();
	m_NanosuitShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());

	m_NanosuitShader->SetFloat3("u_Light.position", { 0.0f, 1.0f, 0.5f });	// for point light

	m_NanosuitShader->SetFloat3("u_Light.ambient", glm::vec3(0.5f));
	m_NanosuitShader->SetFloat3("u_Light.diffuse", glm::vec3(1.0f));
	m_NanosuitShader->SetFloat3("u_Light.specular", glm::vec3(1.0f));

	m_NanosuitShader->SetFloat("u_Light.constant", 1.0f);
	m_NanosuitShader->SetFloat("u_Light.linear", 0.09f);
	m_NanosuitShader->SetFloat("u_Light.quadratic", 0.032f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)) * glm::scale(model, glm::vec3(0.2f));

	m_NanosuitModel->Draw(m_NanosuitShader, model);
	m_NanosuitShader->Unbind();

	irene::Renderer::EndScene();
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
