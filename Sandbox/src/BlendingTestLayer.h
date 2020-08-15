#pragma once

#include <My_OpenGL.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BlendingTestLayer : public myo::Layer
{
public:
	BlendingTestLayer();
	virtual ~BlendingTestLayer();

	virtual void OnAttach() override;
	virtual void OnUpdate(myo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(myo::Event& e) override;

private:
	myo::CameraController m_CameraController;

	/// Cube
	myo::Ref<myo::Texture2D> m_DiffuseMap;

	/// Transparent plane
	std::vector<glm::vec3> m_TransparentPlanePosition;
	myo::Ref<myo::Texture2D> m_TransparentTexture;

};
