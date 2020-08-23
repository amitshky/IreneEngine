#pragma once

#include <Irene.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace irene {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		CameraController m_CameraController;

		Ref<Texture2D> m_CubeTexture;
		Ref<Texture2D> m_PlaneTexture;

		// Framebuffer
		Ref<Framebuffer> m_Framebuffer;

		// Viewport
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		// Cubemaps
		Ref<VertexArray> m_SkyboxVA;
		Ref<VertexBuffer> m_SkyboxVB;
		Ref<Shader> m_SkyboxShader;
		Ref<Texture2D> m_CubemapTexture;
	};

}


