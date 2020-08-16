#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BlendingTestLayer : public irene::Layer
{
public:
	BlendingTestLayer();
	virtual ~BlendingTestLayer();

	virtual void OnAttach() override;
	virtual void OnUpdate(irene::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(irene::Event& e) override;

private:
	irene::CameraController m_CameraController;

	// Cube
	irene::Ref<irene::Texture2D> m_DiffuseMap;

	// Transparent plane
	std::vector<glm::vec3> m_TransparentPlanePosition;
	irene::Ref<irene::Texture2D> m_TransparentTexture;

};
