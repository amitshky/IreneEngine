#include "NanosuitLayer.h"

#include <GLFW/glfw3.h>

NanosuitLayer::NanosuitLayer()
	: Layer("Example"), m_CameraController(16.0f / 9.0f)
{
	float vertices[] = {
		// positions			// normals				// texture coords
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  0.0f,//0
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  0.0f,//1
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  1.0f,//2
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 1.0f,  1.0f,//2
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  1.0f,//3
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	 0.0f,  0.0f,//0

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,//4
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  0.0f,//5
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,//6
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 1.0f,  1.0f,//6
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  1.0f,//7
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	 0.0f,  0.0f,//4

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,//7
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  1.0f,//3
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,//0
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,//0
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 0.0f,  0.0f,//4
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,//7

		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,//6
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  1.0f,//2
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,//1
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  1.0f,//1
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 0.0f,  0.0f,//5
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	 1.0f,  0.0f,//6

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  1.0f,//0
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  1.0f,//1
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  0.0f,//5
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 1.0f,  0.0f,//5
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  0.0f,//4
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	 0.0f,  1.0f,//0

		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  1.0f,//3
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  1.0f,//2
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  0.0f,//6
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 1.0f,  0.0f,//6
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  0.0f,//7
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	 0.0f,  1.0f //3
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

	/// Model loading
	m_NanosuitShader = myo::CreateRef<myo::Shader>("assets/shaders/NonosuitModel.shader");
	m_NanosuitModel = myo::CreateRef<myo::Model>("assets/3DModels/nanosuit/nanosuit.obj");
}

void NanosuitLayer::OnUpdate(myo::Timestep ts)
{
	myo::RenderCommand::SetClearColor({ 0.02f, 0.02f, 0.02f, 1.0f });
	myo::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	myo::Renderer::BeginScene(m_CameraController.GetCamera());

	/// Phong Lighting components
	m_DiffuseColor = glm::vec3(m_LightColor) * m_LightIntensity; // decrease the influence
	m_AmbientColor = m_DiffuseColor * glm::vec3(0.1f); // low influence
	m_SpecularColor = glm::vec3(m_LightColor) * m_LightIntensity;

	/// Light position	// use this to rotate a point light source
	m_LightPos.x = sin(glfwGetTime() * 2.0f);
	m_LightPos.y = sin(glfwGetTime());
	m_LightPos.z = cos(glfwGetTime() * 2.0f);

	glm::mat4 model;

	/// Lamp
	m_LampVA->Bind();
	m_LampShader->Bind();
	m_LampShader->SetFloat3("u_Color", m_LightColor * m_LightIntensity);
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_LightPos) * glm::scale(model, glm::vec3(0.1f));

	myo::Renderer::Submit(m_LampShader, 36, model);
	m_LampVA->Unbind();
	m_LampShader->Unbind();

	/// Nanosuit model
	m_NanosuitShader->Bind();
	m_NanosuitShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());

	//m_NanosuitShader->SetFloat3("u_Light.position", m_CameraController.GetCamera().GetPosition());	// for spot light
	//m_NanosuitShader->SetFloat3("u_Light.direction", m_CameraController.GetCamera().GetFront());
	//m_NanosuitShader->SetFloat("u_Light.cutOff", glm::cos(m_InnerCutOff));
	//m_NanosuitShader->SetFloat("u_Light.outerCutOff", glm::cos(m_OuterCutOff));

	m_NanosuitShader->SetFloat3("u_Light.position", m_LightPos);	// for point light

	m_NanosuitShader->SetFloat3("u_Light.ambient", m_AmbientColor);
	m_NanosuitShader->SetFloat3("u_Light.diffuse", m_DiffuseColor);
	m_NanosuitShader->SetFloat3("u_Light.specular", m_SpecularColor);

	m_NanosuitShader->SetFloat("u_Light.constant", 1.0f);
	m_NanosuitShader->SetFloat("u_Light.linear", 0.09f);
	m_NanosuitShader->SetFloat("u_Light.quadratic", 0.032f);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)) * glm::scale(model, glm::vec3(0.2f));

	m_NanosuitModel->Draw(m_NanosuitShader, model);
	m_NanosuitShader->Unbind();

	myo::Renderer::EndScene();
}

void NanosuitLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Light Color", glm::value_ptr(m_LightColor));
	ImGui::SliderFloat("Light Intensity", &m_LightIntensity, 0.0f, 10.0f);
	ImGui::End();
}

void NanosuitLayer::OnEvent(myo::Event& e)
{
	m_CameraController.OnEvent(e);
}
