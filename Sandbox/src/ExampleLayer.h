#pragma once

#include <My_OpenGL.h>

#include "imgui/imgui.h"

#include "My_OpenGL/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public myo::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(myo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(myo::Event& e) override;

private:
	glm::vec4 m_SquareColor = { 0.0f, 0.7f, 0.7f, 1.0f };
};
