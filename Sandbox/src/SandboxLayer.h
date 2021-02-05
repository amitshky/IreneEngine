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

	irene::Ref<irene::VertexArray> m_CubeVA;
	irene::Ref<irene::VertexBuffer> m_CubeVB;

	irene::Ref<irene::VertexArray> m_QuadVA;
	irene::Ref<irene::VertexBuffer> m_QuadVB;

	irene::Ref<irene::Shader> m_BloomShader;
	irene::Ref<irene::Shader> m_BlurShader;
	irene::Ref<irene::Shader> m_LightShader;
	irene::Ref<irene::Shader> m_BloomFinalShader;
	irene::Ref<irene::Shader> m_FbScreenTexShader;

	irene::Ref<irene::Texture2D> m_WoodTex;
	irene::Ref<irene::Texture2D> m_ContainerTex;

	irene::Ref<irene::Framebuffer> m_BloomFramebuffer;

	std::array<glm::vec3, 4> m_LightPositions;
	std::array<glm::vec3, 4> m_LightColors;

	// UI
	bool m_BloomEnable = true;
	float m_Exposure = 1.0f;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
};

