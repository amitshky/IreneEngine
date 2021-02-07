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
	inline float Lerp(float a, float b, float f) { return a + f * (b - a); }

private:
	irene::CameraController m_CameraController;

	irene::Ref<irene::VertexArray> m_CubeVA;
	irene::Ref<irene::VertexBuffer> m_CubeVB;

	irene::Ref<irene::VertexArray> m_QuadVA;
	irene::Ref<irene::VertexBuffer> m_QuadVB;

	// shaders
	irene::Ref<irene::Shader> m_GeometryPassShader;
	irene::Ref<irene::Shader> m_LightingPassShader;
	irene::Ref<irene::Shader> m_SSAOShader;
	irene::Ref<irene::Shader> m_SSAOBlurShader;
	irene::Ref<irene::Shader> m_TestShader;

	irene::Ref<irene::Model> m_NanosuitModel;

	glm::vec3 m_LightPos   = glm::vec3(2.0f, 4.0f, -2.0f);
	glm::vec3 m_LightColor = glm::vec3(0.2f, 0.2f,  0.7f);

	// G-Buffer
	uint32_t m_GBufferFBO     = 0;
	uint32_t m_PositionBuff   = 0;
	uint32_t m_NormalBuff     = 0;
	uint32_t m_AlbedoSpecBuff = 0;
	uint32_t m_DepthBuffer    = 0;
	// ssao framebuffer
	uint32_t m_NoiseTexture   = 0;
	uint32_t m_SSAOFBO        = 0;
	uint32_t m_SSAOBlurFBO         = 0;
	uint32_t m_SSAOColorBuffer     = 0;
	uint32_t m_SSAOBlurColorBuffer = 0;

	std::array < glm::vec3, 64> m_SSAOKernel; // sample kernel
	std::array < glm::vec3, 16> m_SSAONoise;  // noise texture

	// RNG
	std::mt19937 m_Generator;
	std::uniform_real_distribution<float> m_RandDist;
};
