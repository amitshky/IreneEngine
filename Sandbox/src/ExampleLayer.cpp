#include "ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
}

void ExampleLayer::OnUpdate(myo::Timestep ts)
{
	glClearColor(m_SquareColor.x, m_SquareColor.y, m_SquareColor.z, m_SquareColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(myo::Event& e)
{
}
