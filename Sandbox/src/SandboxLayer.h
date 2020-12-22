#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SandboxLayer : public irene::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(irene::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(irene::Event& e) override;

private:
	irene::CameraController m_CameraController;

	irene::Ref<irene::VertexArray> m_VA;
	irene::Ref<irene::VertexBuffer> m_VB;

	irene::Ref<irene::Shader> m_Shader;
	irene::Ref<irene::Texture2D> m_DiffuseMap;
	irene::Ref<irene::Texture2D> m_SpecularMap;
	irene::Ref<irene::Texture2D> m_NormalMap;
	irene::Ref<irene::Texture2D> m_HeightMap;

	glm::vec3 m_LightPos = glm::vec3(0.0f);
};

