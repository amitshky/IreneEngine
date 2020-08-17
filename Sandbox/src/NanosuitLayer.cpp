#include "NanosuitLayer.h"

#include <GLFW/glfw3.h>

NanosuitLayer::NanosuitLayer()
	: Layer("Nanosuit"), m_CameraController(16.0f / 9.0f)
{
	
}

void NanosuitLayer::OnAttach()
{
	// Model loading
	m_NanosuitShader = irene::Shader::Create("assets/shaders/NanosuitModel.shader");
	m_NanosuitModel = irene::CreateRef<irene::Model>("assets/3DModels/nanosuit/nanosuit.obj");
}

void NanosuitLayer::OnDetach()
{
}

void NanosuitLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	irene::Renderer::BeginScene(m_CameraController.GetCamera());

	// Nanosuit model
	m_NanosuitShader->Bind();
	m_NanosuitShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());

	//m_NanosuitShader->SetFloat3("u_Light.position", m_CameraController.GetCamera().GetPosition());	// for spot light
	//m_NanosuitShader->SetFloat3("u_Light.direction", m_CameraController.GetCamera().GetFront());
	//m_NanosuitShader->SetFloat("u_Light.cutOff", glm::cos(m_InnerCutOff));
	//m_NanosuitShader->SetFloat("u_Light.outerCutOff", glm::cos(m_OuterCutOff));

	m_NanosuitShader->SetFloat3("u_Light.position", m_LightPos);	// for point light

	m_NanosuitShader->SetFloat3("u_Light.ambient", m_AmbientColor);
	m_NanosuitShader->SetFloat3("u_Light.diffuse", m_DiffuseColor);
	m_NanosuitShader->SetFloat3("u_Light.specular", m_SpecularColor);

	m_NanosuitShader->SetFloat("u_Light.constant", 1.0f);
	m_NanosuitShader->SetFloat("u_Light.linear", 0.09f);
	m_NanosuitShader->SetFloat("u_Light.quadratic", 0.032f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)) * glm::scale(model, glm::vec3(0.2f));

	m_NanosuitModel->Draw(m_NanosuitShader, model);
	m_NanosuitShader->Unbind();

	irene::Renderer::EndScene();

	// Phong Lighting components
	m_DiffuseColor = glm::vec3(m_LightColor) * m_LightIntensity; // decrease the influence
	m_AmbientColor = m_DiffuseColor * glm::vec3(0.1f); // low influence
	m_SpecularColor = glm::vec3(m_LightColor) * m_LightIntensity;

	// Light position	// use this to rotate a point light source
	m_LightPos.x = sin(glfwGetTime() * 2.0f);
	m_LightPos.y = sin(glfwGetTime());
	m_LightPos.z = cos(glfwGetTime() * 2.0f);

	irene::Renderer3D::BeginScene(m_CameraController.GetCamera());
	// Lamp
	irene::Renderer3D::DrawColoredCube(m_LightColor * m_LightIntensity, m_LightPos, glm::vec3(0.2f));
	irene::Renderer3D::EndScene();
}

void NanosuitLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Light Color", glm::value_ptr(m_LightColor));
	ImGui::SliderFloat("Light Intensity", &m_LightIntensity, 0.0f, 10.0f);
	ImGui::End();
}

void NanosuitLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
