#include "BlendingTestLayer.h"

#include <GLFW/glfw3.h>

BlendingTestLayer::BlendingTestLayer()
	: Layer("Blending Test"), m_CameraController(16.0f / 9.0f)
{
	m_TransparentPlanePosition.push_back(glm::vec3(0.3f, 0.0f, 1.8f));
	m_TransparentPlanePosition.push_back(glm::vec3(0.5f, 0.0f, 1.5f));
	
	m_TransparentTexture = myo::CreateRef<myo::Texture2D>("assets/textures/transparentWindow.png");
}

BlendingTestLayer::~BlendingTestLayer()
{
}

void BlendingTestLayer::OnAttach()
{
	m_DiffuseMap = myo::CreateRef<myo::Texture2D>("assets/textures/container2.png");
}

void BlendingTestLayer::OnUpdate(myo::Timestep ts)
{
	myo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	myo::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	myo::Renderer3D::BeginScene(m_CameraController.GetCamera());
	myo::Renderer3D::DrawTexturedCube(m_DiffuseMap, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	myo::Renderer3D::DrawTexturedCube(m_DiffuseMap, { 0.5f, 0.0f, -1.2f }, { 1.0f, 1.0f, 1.0f });
	
	// sort the transparent windows before rendering
	std::map<float, glm::vec3> sorted; // map sorts data based on 'key' (key here is distance)
	for (unsigned int i = 0; i < m_TransparentPlanePosition.size(); i++)
	{
		float distance = glm::length(m_CameraController.GetCamera().GetPosition() - m_TransparentPlanePosition[i]);
		sorted[distance] = m_TransparentPlanePosition[i];
	}

	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		myo::Renderer3D::DrawTexturedPlane(m_TransparentTexture, it->second, 0.0f, { 0.0f, 0.0f, 1.0f }, glm::vec3(1.0f));

	myo::Renderer3D::EndScene();
}

void BlendingTestLayer::OnImGuiRender()
{
}

void BlendingTestLayer::OnEvent(myo::Event& e)
{
	m_CameraController.OnEvent(e);
}
