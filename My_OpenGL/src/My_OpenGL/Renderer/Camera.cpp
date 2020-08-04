#include "pch.h"
#include "Camera.h"

namespace myo {

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
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f))/*, m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)*/
	{
		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = pitch;

		RecalculateViewMatrix();
	}

	//Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	//	: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
	//{
	//	m_Position = glm::vec3(posX, posY, posZ);
	//	m_WorldUp = glm::vec3(upX, upY, upZ);
	//	m_Yaw = yaw;
	//	m_Pitch = pitch;
	//	UpdateCameraVectors();
	//}

	//glm::mat4 Camera::GetViewMatrix()
	//{
	//	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	//}

	//void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
	//{
	//	float velocity = m_MovementSpeed * deltaTime;
	//	if (direction == CameraMovement::FORWARD)
	//		m_Position += m_Front * velocity;
	//	if (direction == CameraMovement::BACKWARD)
	//		m_Position -= m_Front * velocity;
	//	if (direction == CameraMovement::LEFT)
	//		m_Position -= m_Right * velocity;
	//	if (direction == CameraMovement::RIGHT)
	//		m_Position += m_Right * velocity;
	//	if (direction == CameraMovement::UP)
	//		m_Position += m_Up * velocity;
	//	if (direction == CameraMovement::DOWN)
	//		m_Position -= m_Up * velocity;
	//	if (direction == CameraMovement::PITCHUP)
	//		m_Pitch += velocity * 15.0f;
	//	if (direction == CameraMovement::PITCHDOWN)
	//		m_Pitch -= velocity * 15.0f;
	//	if (direction == CameraMovement::YAWLEFT)
	//		m_Yaw -= velocity * 15.0f;
	//	if (direction == CameraMovement::YAWRIGHT)
	//		m_Yaw += velocity * 15.0f;

	//	if (m_Pitch > 89.0f)
	//		m_Pitch = 89.0f;
	//	if (m_Pitch < -89.0f)
	//		m_Pitch = -89.0f;

	//	UpdateCameraVectors();
	//}

	//void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	//{
	//	xoffset *= m_MouseSensitivity;
	//	yoffset *= m_MouseSensitivity;

	//	m_Yaw += xoffset;
	//	m_Pitch += yoffset;

	//	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	//	if (constrainPitch)
	//	{
	//		if (m_Pitch > 89.0f)
	//			m_Pitch = 89.0f;
	//		if (m_Pitch < -89.0f)
	//			m_Pitch = -89.0f;
	//	}

	//	// Update Front, Right and Up Vectors using the updated Euler angles
	//	UpdateCameraVectors();
	//}

	//void Camera::ProcessMouseScroll(float yoffset)
	//{
	//	if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
	//		m_Zoom -= yoffset;
	//	if (m_Zoom <= 1.0f)
	//		m_Zoom = 1.0f;
	//	if (m_Zoom >= 45.0f)
	//		m_Zoom = 45.0f;
	//}

	//void Camera::UpdateCameraVectors()
	//{
	//	glm::vec3 front;
	//	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	//	front.y = sin(glm::radians(m_Pitch));
	//	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	//	m_Front = glm::normalize(front);
	//	// Also re-calculate the Right and Up vector
	//	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	//}

	

}
