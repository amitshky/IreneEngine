#pragma once

#include "Irene/Core/Timestep.h"
#include "Irene/Renderer/Camera.h"
#include "Irene/Events/ApplicationEvent.h"
#include "Irene/Events/MouseEvent.h"

namespace irene {

	class CameraController
	{
	public:
		CameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		void CalculateView();

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		inline float GetZoomLevel() const { return m_ZoomLevel; }
		inline void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		std::pair<float, float> CalcMouseOffset(float xpos, float ypos);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 45.0f;

		Camera m_Camera;
		glm::vec3 m_CameraPosition = glm::vec3(0.0f);
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraMovSpeed = 0.1f;

		float m_MouseSensitivity = 0.1f;
		bool m_MousePositionReset = true;
		float m_PrevMouseX = 0.0f;
		float m_PrevMouseY = 0.0f;

	};

}
