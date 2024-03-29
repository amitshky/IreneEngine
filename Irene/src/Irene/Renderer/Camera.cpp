#include "pch.h"
#include "Camera.h"

namespace irene {

	Camera::Camera(float aspectRatio, float zoom, glm::vec3& position, glm::vec3& up, float yaw, float pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
	{
		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = pitch;

		RecalculateViewMatrix();
		SetProjection(zoom, aspectRatio);
	}

	void Camera::SetProjection(float zoom, float aspectRatio)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
