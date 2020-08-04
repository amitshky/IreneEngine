#include "NanosuitLayer.h"

#include <GLFW/glfw3.h>

NanosuitLayer::NanosuitLayer()
	: Layer("Example"), m_Camera(glm::vec3(0.0f, 0.0f, 3.0f)), m_CameraController(16.0f / 9.0f)
{
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Depth testing
	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
		// positions			// normals				// texture coords
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  1.0f
	};

	/// Lamp object
	m_LampVA = myo::CreateRef<myo::VertexArray>();
	m_LampVBO = myo::CreateRef<myo::VertexBuffer>(vertices, sizeof(vertices));
	m_LampVBO->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float3, "a_Normal"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_LampVA->AddVertexBuffer(m_LampVBO);
	m_LampShader = myo::CreateRef<myo::Shader>("assets/shaders/Light.shader");
	m_LampVBO->Unbind();
	m_LampVA->Unbind();
	m_LampShader->Unbind();

	/// Phong Lighting component's intensity
	m_DiffuseColor = glm::vec3(0.8f) * 3.0f; // decrease the influence
	m_AmbientColor = m_DiffuseColor * glm::vec3(0.2f); // low influence
	m_SpecularColor = glm::vec3(1.0f);

	/// Model loading
	m_NanosuitShader = myo::CreateRef<myo::Shader>("assets/shaders/ModelLoading.shader");
	m_NanosuitModel = myo::CreateRef<myo::Model>("assets/3DModels/nanosuit/nanosuit.obj");
}

void NanosuitLayer::OnUpdate(myo::Timestep ts)
{
	glClearColor(m_BgColor.x, m_BgColor.y, m_BgColor.z, m_BgColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_CameraController.OnUpdate(ts);

	/// Light position	// use this to rotate a point light source
	m_LightPos.x = sin(glfwGetTime() * 2.0f);
	m_LightPos.y = sin(glfwGetTime());
	m_LightPos.z = cos(glfwGetTime() * 2.0f);

	// view/projection transformation
	//m_Camera.SetProjection(45.0f, 16.0f / 9.0f);
	glm::mat4 projection = m_CameraController.GetCamera().GetProjectionMatrix();
	glm::mat4 view = m_CameraController.GetCamera().GetViewMatrix();
	// world coordinates
	glm::mat4 model;

	/// Lamp
	m_LampShader->Bind();
	m_LampShader->SetMat4("u_Projection", projection);
	m_LampShader->SetMat4("u_View", view);
	m_LampVA->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_LightPos);
	model = glm::scale(model, glm::vec3(0.1f));
	m_LampShader->SetMat4("u_Model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_LampVA->Unbind();
	m_LampShader->Unbind();

	/// Nanosuit model
	m_NanosuitShader->Bind();
	m_NanosuitShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());

	//m_NanosuitShader->SetFloat3("u_Light.position", m_Camera.GetPosition());	// for spot light
	//m_NanosuitShader->SetFloat3("u_Light.direction", m_Camera.GetFront());
	m_NanosuitShader->SetFloat("u_Light.cutOff", glm::cos(m_InnerCutOff));
	m_NanosuitShader->SetFloat("u_Light.m_OuterCutOff", glm::cos(m_OuterCutOff));

	m_NanosuitShader->SetFloat3("u_Light.position", m_LightPos);	// for point light

	m_NanosuitShader->SetFloat3("u_Light.ambient", m_AmbientColor);
	m_NanosuitShader->SetFloat3("u_Light.diffuse", m_DiffuseColor);
	m_NanosuitShader->SetFloat3("u_Light.specular", m_SpecularColor);

	m_NanosuitShader->SetFloat("u_Light.constant", 1.0f);
	m_NanosuitShader->SetFloat("u_Light.linear", 0.09f);
	m_NanosuitShader->SetFloat("u_Light.quadratic", 0.032f);

	m_NanosuitShader->SetMat4("u_Projection", projection);
	m_NanosuitShader->SetMat4("u_View", view);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f));
	m_NanosuitShader->SetMat4("u_Model", model);

	m_NanosuitModel->Draw(m_NanosuitShader);
	m_NanosuitShader->Unbind();
}

void NanosuitLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BgColor));
	ImGui::End();
}

void NanosuitLayer::OnEvent(myo::Event& e)
{
	m_CameraController.OnEvent(e);
}
