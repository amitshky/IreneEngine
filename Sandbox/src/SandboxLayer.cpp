#include <GLFW/glfw3.h>
#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
	: Layer("Sandbox Layer"), m_CameraController(16.0f / 9.0f)
{
	m_CubeTexture = irene::Texture2D::Create("assets/textures/container.jpg");
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
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
	irene::Renderer3D::DrawCube(m_Position, glm::vec3(1.0f), m_CubeTexture);
	irene::Renderer3D::EndScene();
}

void SandboxLayer::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//ImGui::SliderFloat3("Position", glm::value_ptr(m_Position), -10.0f, 10.0f);
	//ImGui::End();
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
