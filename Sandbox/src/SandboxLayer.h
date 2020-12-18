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
	void RenderScene(const irene::Ref<irene::Shader>& shader);

private:
	irene::CameraController m_CameraController;

	irene::Ref<irene::Texture2D> m_Texture;

	uint32_t m_DepthMapFBO = 0;
	uint32_t m_DepthCubemap = 0;
	uint32_t m_ShadowWidth = 1024, m_ShadowHeight = 1024;

	irene::Ref<irene::Shader> m_Shader;
	irene::Ref<irene::Shader> m_CubemapDepthShader;

	irene::Ref<irene::VertexArray> m_CubeVA;
	irene::Ref<irene::VertexBuffer> m_CubeVB;
	irene::Ref<irene::VertexArray> m_PlaneVA;
	irene::Ref<irene::VertexBuffer> m_PlaneVB;

	uint32_t m_Width = 1280, m_Height = 720;

	glm::vec3 m_LightPos = glm::vec3(0.0f);
	glm::mat4 m_ShadowProj;
	std::array<glm::mat4, 6> m_ShadowTransforms;
};

