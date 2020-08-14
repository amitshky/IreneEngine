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

	void OnUpdate(myo::Timestep ts);
	virtual void OnImGuiRender();
	void OnEvent(myo::Event& e);

private:
	myo::CameraController m_CameraController;

	/// Cube
	myo::Ref<myo::VertexArray> m_CubeVA;
	myo::Ref<myo::VertexBuffer> m_CubeVB;
	myo::Ref<myo::Shader> m_CubeShader;

	myo::Ref<myo::Texture2D> m_DiffuseMap;

	/// Transparent plane
	std::vector<glm::vec3> m_TransparentPlanePosition;

	myo::Ref<myo::VertexArray> m_TransparentVA;
	myo::Ref<myo::VertexBuffer> m_TransparentVB;
	myo::Ref<myo::Shader> m_TransparentShader;

	myo::Ref<myo::Texture2D> m_TransparentTexture;

};
