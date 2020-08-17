#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeLayer : public irene::Layer
{
public:
	CubeLayer();
	virtual ~CubeLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(irene::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(irene::Event& e) override;

private:
	irene::CameraController m_CameraController;

	irene::Ref<irene::Texture2D> m_DiffuseMap;
	irene::Ref<irene::Texture2D> m_SpecularMap;

	// Light properties
	glm::vec3 m_LightPos = glm::vec3(1.0f, 1.0f, 1.5f);
	glm::vec3 m_DiffuseColor = glm::vec3(0.0f);
	glm::vec3 m_AmbientColor = glm::vec3(0.0f);
	glm::vec3 m_SpecularColor = glm::vec3(0.0f);

	glm::vec4 m_LightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_LightIntensity = 1.0f;
};
