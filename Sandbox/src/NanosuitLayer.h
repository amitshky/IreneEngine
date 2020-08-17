#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class NanosuitLayer : public irene::Layer
{
public:
	NanosuitLayer();
	virtual ~NanosuitLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(irene::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(irene::Event& e) override;

private:
	irene::CameraController m_CameraController;

	// Spot Light properties // uncomment code in shader as well
	//float m_InnerCutOff = glm::radians(12.5f);
	//float m_OuterCutOff = glm::radians(20.0f);

	irene::Ref<irene::Shader> m_NanosuitShader;
	irene::Ref<irene::Model> m_NanosuitModel;

	// Light properties
	glm::vec3 m_LightPos = glm::vec3(1.0f, 1.0f, 1.5f);
	glm::vec3 m_DiffuseColor = glm::vec3(1.0f);
	glm::vec3 m_AmbientColor = glm::vec3(1.0f);
	glm::vec3 m_SpecularColor = glm::vec3(1.0f);

	glm::vec4 m_LightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_LightIntensity = 3.0f;
};
