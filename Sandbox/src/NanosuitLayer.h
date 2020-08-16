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

	virtual void OnAttach() override;
	virtual void OnUpdate(myo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(myo::Event& e) override;

private:
	myo::CameraController m_CameraController;

	// Spot Light properties
	//float m_InnerCutOff = glm::radians(12.5f);
	//float m_OuterCutOff = glm::radians(20.0f);

	myo::Ref<myo::Shader> m_NanosuitShader;
	myo::Ref<myo::Model> m_NanosuitModel;

	// Light properties
	glm::vec3 m_LightPos = glm::vec3(1.0f, 1.0f, 1.5f);
	glm::vec3 m_DiffuseColor;
	glm::vec3 m_AmbientColor;
	glm::vec3 m_SpecularColor;

	glm::vec4 m_LightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_LightIntensity = 3.0f;
};
