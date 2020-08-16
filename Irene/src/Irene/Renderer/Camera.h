#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>

#include <vector>

namespace irene {

	class Camera
	{
	public:
		Camera(float aspectRatio, float zoom, glm::vec3& position = glm::vec3(0.0f), glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		void SetProjection(float zoom, float aspectRatio);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		const glm::vec3& GetFront() const { return m_Front; }
		const glm::vec3& GetUp() const { return m_Up; }
		const glm::vec3& GetRight() const { return m_Right; }

		void UpdatePitch(float pitch) { m_Pitch += pitch; }
		float GetPitch() { return m_Pitch; }
		void UpdateYaw(float yaw) { m_Yaw += yaw; }
		float GetYaw() { return m_Yaw; }

		void ClampPitch(float min, float max)
		{
			m_Pitch = std::max(m_Pitch, min);
			m_Pitch = std::min(m_Pitch, max);
		}

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		////////////////////
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		float m_Yaw;
		float m_Pitch;
	};

}
