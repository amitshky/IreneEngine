#include "pch.h"
#include "CameraController.h"
#include "My_OpenGL/Core/Input.h"
#include "My_OpenGL/Core/KeyCodes.h"
#include "My_OpenGL/Core/MouseButtonCodes.h"

namespace myo {

	CameraController::CameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(aspectRatio, m_ZoomLevel, glm::vec3(0.0f, 0.0f, 3.0f)), m_Rotation(rotation)
	{
		m_CameraPosition = m_Camera.GetPosition();
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		// Camera Movement
		m_CameraTranslationSpeed = m_CameraMovSpeed * m_ZoomLevel * ts;
		if (Input::IsKeyPressed(KEY_A))
			m_CameraPosition -= m_Camera.GetRight() * m_CameraTranslationSpeed;
		else if (Input::IsKeyPressed(KEY_D))
			m_CameraPosition += m_Camera.GetRight() * m_CameraTranslationSpeed;

		if (Input::IsKeyPressed(KEY_W))
			m_CameraPosition += m_Camera.GetFront() * m_CameraTranslationSpeed;
		else if (Input::IsKeyPressed(KEY_S))
			m_CameraPosition -= m_Camera.GetFront() * m_CameraTranslationSpeed;

		if (Input::IsKeyPressed(KEY_E))
			m_CameraPosition += m_Camera.GetUp() * m_CameraTranslationSpeed;
		else if (Input::IsKeyPressed(KEY_Q))
			m_CameraPosition -= m_Camera.GetUp() * m_CameraTranslationSpeed;

		m_Camera.SetPosition(m_CameraPosition);
		
		// Camera Rotation
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(KEY_R))
				m_CameraRotation += m_CameraRotSpeed * ts;
			else if (Input::IsKeyPressed(KEY_F))
				m_CameraRotation -= m_CameraRotSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 1.0f);
		m_ZoomLevel = std::min(m_ZoomLevel, 90.0f);
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio);
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio);
		return false;
	}

}