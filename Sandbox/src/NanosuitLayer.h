#pragma once

#include <My_OpenGL.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class NanosuitLayer : public myo::Layer
{
public:
	NanosuitLayer();
	virtual ~NanosuitLayer() = default;

	void OnUpdate(myo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(myo::Event& e) override;

private:
	myo::Camera m_Camera;
	myo::CameraController m_CameraController;

	/// Spot Light properties
	float m_InnerCutOff = glm::radians(12.5f);
	float m_OuterCutOff = glm::radians(20.0f);

	myo::Ref<myo::VertexArray> m_LampVA;
	myo::Ref<myo::VertexBuffer> m_LampVBO;
	myo::Ref<myo::Shader> m_LampShader;

	myo::Ref<myo::Shader> m_NanosuitShader;
	myo::Ref<myo::Model> m_NanosuitModel;

	/// Light properties
	glm::vec3 m_LightPos = glm::vec3(1.0f, 1.0f, 1.5f);
	glm::vec3 m_DiffuseColor;
	glm::vec3 m_AmbientColor;
	glm::vec3 m_SpecularColor;

	glm::vec4 m_BgColor = { 0.05f, 0.05f, 0.05f, 1.0f };
};
