#include "pch.h"
#include "CameraController.h"
#include "Irene/Core/Input.h"
#include "Irene/Core/KeyCodes.h"
#include "Irene/Core/MouseButtonCodes.h"

namespace irene {

	CameraController::CameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(aspectRatio, m_ZoomLevel, glm::vec3(0.0f, 0.0f, 3.0f))
	{
		m_CameraPosition = m_Camera.GetPosition();
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		// Camera Movement
		if (Input::IsMouseButtonPressed(MOUSE_BUTTON_5) || Input::IsKeyPressed(KEY_LEFT_SHIFT))
		{
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

			if (Input::IsKeyPressed(KEY_UP))
				m_CameraPosition += m_Camera.GetUp() * m_CameraTranslationSpeed;
			else if (Input::IsKeyPressed(KEY_DOWN))
				m_CameraPosition -= m_Camera.GetUp() * m_CameraTranslationSpeed;
		}

		if ((Input::IsMouseButtonPressed(MOUSE_BUTTON_5) && (Input::GetMouseX() || Input::GetMouseY())) || 
			(Input::IsKeyPressed(KEY_LEFT_SHIFT) && (Input::GetMouseX() || Input::GetMouseY())))
		{
			float xpos = Input::GetMouseX();
			float ypos = Input::GetMouseY();

			auto[xoffset, yoffset] = CalcMouseOffset(xpos, ypos);

			m_Camera.UpdateYaw(xoffset);
			m_Camera.UpdatePitch(yoffset);

			m_Camera.ClampPitch(-89.0f, 89.0f);
		}
		else if (Input::IsMouseButtonReleased(MOUSE_BUTTON_5) || Input::IsKeyReleased(KEY_LEFT_SHIFT))
			m_MousePositionReset = true;

		m_Camera.SetPosition(m_CameraPosition);
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	void CameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		CalculateView();
	}

	void CameraController::CalculateView()
	{
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio);
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.1f);
		m_ZoomLevel = std::min(m_ZoomLevel, 90.0f);
		CalculateView();
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = e.GetWidth() && e.GetHeight() ? (float)e.GetWidth() / (float)e.GetHeight() : 0;
		CalculateView();
		return false;
	}

	std::pair<float, float> CameraController::CalcMouseOffset(float xpos, float ypos)
	{
		if (m_MousePositionReset)
		{
			m_PrevMouseX = xpos;
			m_PrevMouseY = ypos;
			m_MousePositionReset = false;
		}

		float xoffset = xpos - m_PrevMouseX;
		float yoffset = m_PrevMouseY - ypos;
		m_PrevMouseX = xpos;
		m_PrevMouseY = ypos;

		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		return { xoffset, yoffset };
	}

}