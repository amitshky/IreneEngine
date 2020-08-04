#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>

#include <vector>

namespace myo {

	enum class CameraMovement : int {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		PITCHUP,
		PITCHDOWN,
		YAWLEFT,
		YAWRIGHT
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.05f;
	const float ZOOM = 45.0f;

	class Camera
	{
	public:
		Camera(float aspectRatio, float zoom, glm::vec3& position = glm::vec3(0.0f), glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		void SetProjection(float zoom, float aspectRatio);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		const glm::vec3& GetFront() const { return m_Front; }
		const glm::vec3& GetUp() const { return m_Up; }
		const glm::vec3& GetRight() const { return m_Right; }

		///////////////////////////////////////////////////

		Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		//Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		//glm::mat4 GetViewMatrix();
		//void ProcessKeyboard(CameraMovement direction, float deltaTime);
		//void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		//void ProcessMouseScroll(float yoffset);

		//inline float GetZoom() const { return m_Zoom; }
		////inline glm::vec3 GetPosition() const { return m_Position; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		////////////////////
		//glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		float m_Yaw;
		float m_Pitch;

		//float m_MovementSpeed;
		//float m_MouseSensitivity;
		//float m_Zoom;
	};

}
