#pragma once

#include <My_OpenGL.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubeLayer : public myo::Layer
{
public:
	CubeLayer();
	virtual ~CubeLayer();

	virtual void OnAttach() override;
	virtual void OnUpdate(myo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(myo::Event& e) override;

private:
	myo::CameraController m_CameraController;

	myo::Ref<myo::Texture2D> m_DiffuseMap;
	myo::Ref<myo::Texture2D> m_SpecularMap;

	/// Light properties
	glm::vec3 m_LightPos = glm::vec3(1.0f, 1.0f, 1.5f);
	glm::vec3 m_DiffuseColor = glm::vec3(0.0f);
	glm::vec3 m_AmbientColor = glm::vec3(0.0f);
	glm::vec3 m_SpecularColor = glm::vec3(0.0f);

	glm::vec4 m_LightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_LightIntensity = 1.0f;
};
