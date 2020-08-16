#include "CubeLayer.h"

#include <GLFW/glfw3.h>

CubeLayer::CubeLayer()
	: Layer("Cube"), m_CameraController(16.0f / 9.0f)
{
}

CubeLayer::~CubeLayer()
{
}

void CubeLayer::OnAttach()
{
	m_DiffuseMap = irene::CreateRef<irene::Texture2D>("assets/textures/container2.png");
	m_SpecularMap = irene::CreateRef<irene::Texture2D>("assets/textures/container2_specular.png");
}

void CubeLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_LightPos.x = sin(glfwGetTime() * 2.0f);
	m_LightPos.y = sin(glfwGetTime());
	m_LightPos.z = cos(glfwGetTime() * 2.0f);

	// Phong Lighting components
	m_DiffuseColor = glm::vec3(m_LightColor) * m_LightIntensity; // decrease the influence
	m_AmbientColor = m_DiffuseColor * glm::vec3(0.1f); // low influence
	m_SpecularColor = glm::vec3(m_LightColor) * m_LightIntensity;

	irene::LightData lightData(m_LightPos, m_AmbientColor, m_DiffuseColor, m_SpecularColor);

	m_CameraController.OnUpdate(ts);
	irene::Renderer3D::BeginScene(m_CameraController.GetCamera());
	irene::Renderer3D::DrawCubeWithLighting(m_DiffuseMap, m_SpecularMap, lightData, { 0.0f, 0.0f, 0.0f }, glm::vec3(1.0f)); // Cube with lighting
	irene::Renderer3D::DrawTexturedCube(m_DiffuseMap, { 2.0f, 0.0f, 0.0f }, glm::vec3(1.0f));	// cube with only texture
	irene::Renderer3D::DrawColoredCube(m_LightColor * m_LightIntensity, m_LightPos, glm::vec3(0.2f));	// lamp

	irene::Renderer3D::EndScene();
}

void CubeLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Light Color", glm::value_ptr(m_LightColor));
	ImGui::SliderFloat("Light Intensity", &m_LightIntensity, 0.0f, 10.0f);
	ImGui::End();
}

void CubeLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
