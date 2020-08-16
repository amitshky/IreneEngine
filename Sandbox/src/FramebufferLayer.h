#pragma once

#include <My_OpenGL.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FramebufferLayer : public myo::Layer
{
public:
	FramebufferLayer();
	virtual ~FramebufferLayer();

	virtual void OnAttach() override;
	virtual void OnUpdate(myo::Timestep ts) override;
	virtual virtual void OnImGuiRender() override;
	virtual void OnEvent(myo::Event& e) override;

private:
	myo::CameraController m_CameraController;

	myo::Ref<myo::Shader> m_Shader;
	myo::Ref<myo::Shader> m_ScreenShader;

	myo::Ref<myo::Texture2D> m_CubeTexture;
	myo::Ref<myo::Texture2D> m_PlaneTexture;

	// Framebuffer
	myo::Ref<myo::Framebuffer> m_Framebuffer;
	myo::Ref<myo::VertexArray> m_QuadVA;	// to fill the entire viewport
	myo::Ref<myo::VertexBuffer> m_QuadVB;
	myo::Ref<myo::Shader> m_QuadShader;
};
