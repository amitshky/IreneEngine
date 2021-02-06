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

	irene::Ref<irene::Shader> m_GeometryPassShader;
	irene::Ref<irene::Shader> m_LightingPassShader;
	irene::Ref<irene::Shader> m_LightBoxShader;

	irene::Ref<irene::Model> m_NanosuitModel;
	std::array<glm::vec3, 9> m_NanosuitPositions;

	std::array<glm::vec3, 32> m_LightPositions;
	std::array<glm::vec3, 32> m_LightColors;

	// G-Buffer
	uint32_t m_GBufferFBO     = 0;
	uint32_t m_PositionBuff   = 0;
	uint32_t m_NormalBuff     = 0;
	uint32_t m_AlbedoSpecBuff = 0;
	uint32_t m_DepthBuffer    = 0;

	// RNG
	std::mt19937 m_Generator;
	std::uniform_real_distribution<float> m_RandDist;

	// UI
	//bool m_BloomEnable = true;
	//float m_Exposure = 1.0f;
	//glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
};

