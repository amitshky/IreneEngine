#pragma once

#include <My_OpenGL.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public myo::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(myo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(myo::Event& e) override;

private:
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	myo::Camera camera;
	/// Spot Light properties
	float innerCutOff = glm::radians(12.5f);
	float outerCutOff = glm::radians(20.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.5f);
	myo::Ref<myo::VertexArray> CubeVA;
	myo::Ref<myo::VertexBuffer> vbo;
	myo::Ref<myo::Shader> CubeShader;
	myo::Ref<myo::VertexArray> LampVA;
	myo::Ref<myo::Shader> LampShader;
	myo::Ref<myo::Shader> nanosuitShader;
	myo::Ref<myo::Model> nanosuitModel;
	glm::vec3 diffuseColor;
	glm::vec3 ambientColor;
	glm::vec3 specularColor;

	glm::vec4 m_BgColor = { 0.2f, 0.2f, 0.2f, 1.0f };
};
