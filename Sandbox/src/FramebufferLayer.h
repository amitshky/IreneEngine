#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FramebufferLayer : public irene::Layer
{
public:
	FramebufferLayer();
	virtual ~FramebufferLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(irene::Timestep ts) override;
	virtual virtual void OnImGuiRender() override;
	virtual void OnEvent(irene::Event& e) override;

private:
	irene::CameraController m_CameraController;

	irene::Ref<irene::Shader> m_ScreenShader;

	irene::Ref<irene::Texture2D> m_CubeTexture;
	irene::Ref<irene::Texture2D> m_PlaneTexture;

	// Framebuffer
	irene::Ref<irene::Framebuffer> m_Framebuffer;
	irene::Ref<irene::VertexArray> m_QuadVA;	// to fill the entire viewport
	irene::Ref<irene::VertexBuffer> m_QuadVB;
	irene::Ref<irene::Shader> m_QuadShader;
};
