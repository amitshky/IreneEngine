#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CubemapLayer : public irene::Layer
{
public:
	CubemapLayer();
	virtual ~CubemapLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(irene::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(irene::Event& e) override;

private:
	irene::CameraController m_CameraController;

	irene::Ref<irene::VertexArray> m_SkyboxVA;
	irene::Ref<irene::VertexBuffer> m_SkyboxVB;
	irene::Ref<irene::Shader> m_SkyboxShader;
	irene::Ref<irene::Texture2D> m_CubemapTexture;
	irene::Ref<irene::Texture2D> m_CubeTexture;
};
