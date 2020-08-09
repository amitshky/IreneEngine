#include "CubeLayer.h"

#include <GLFW/glfw3.h>

CubeLayer::CubeLayer()
	: Layer("Cube"), m_CameraController(16.0f / 9.0f)
{
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

	float transparentVertices[] = {
		// positions		// texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	/// Cube
	m_CubeVA = myo::CreateRef<myo::VertexArray>();
	m_CubeVB = myo::CreateRef<myo::VertexBuffer>(vertices, sizeof(vertices));
	m_CubeVB->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float3, "a_Normal"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_CubeVA->AddVertexBuffer(m_CubeVB);

	m_CubeShader = myo::CreateRef<myo::Shader>("assets/shaders/MultipleLights.shader");
	m_CubeShader->Bind();
	m_DiffuseMap = myo::CreateRef<myo::Texture2D>("assets/textures/container2.png");
	m_CubeShader->SetInt("u_Material.diffuse", 0);
	m_SpecularMap = myo::CreateRef<myo::Texture2D>("assets/textures/container2_specular.png");
	m_CubeShader->SetInt("u_Material.specular", 1);
	m_CubeShader->SetFloat("u_Material.shininess", 64.0f);

	m_CubeShader->Unbind();
	m_CubeVB->Unbind();
	m_CubeVA->Unbind();

	/// Lamp object
	m_LampVA = myo::CreateRef<myo::VertexArray>();
	m_LampVBO = myo::CreateRef<myo::VertexBuffer>(vertices, sizeof(vertices));
	m_LampVBO->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float3, "a_Normals"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_LampVA->AddVertexBuffer(m_LampVBO);

	m_LampShader = myo::CreateRef<myo::Shader>("assets/shaders/Light.shader");

	m_LampVBO->Unbind();
	m_LampVA->Unbind();
	m_LampShader->Unbind();
}

CubeLayer::~CubeLayer()
{
}

void CubeLayer::OnUpdate(myo::Timestep ts)
{
	myo::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1.0f });
	myo::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	myo::Renderer::BeginScene(m_CameraController.GetCamera());

	m_LightPos.x = sin(glfwGetTime() * 2.0f);
	m_LightPos.y = sin(glfwGetTime());
	m_LightPos.z = cos(glfwGetTime() * 2.0f);

	/// Phong Lighting components
	m_DiffuseColor = glm::vec3(m_LightColor) * m_LightIntensity; // decrease the influence
	m_AmbientColor = m_DiffuseColor * glm::vec3(0.1f); // low influence
	m_SpecularColor = glm::vec3(m_LightColor) * m_LightIntensity;

	glm::mat4 model;

	m_CubeShader->Bind();
	m_CubeShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());
	m_CubeShader->SetFloat3("u_PointLight[0].position", m_LightPos);
	m_CubeShader->SetFloat3("u_PointLight[0].ambient", m_AmbientColor);
	m_CubeShader->SetFloat3("u_PointLight[0].diffuse", m_DiffuseColor);
	m_CubeShader->SetFloat3("u_PointLight[0].specular", m_SpecularColor);
	m_CubeShader->SetFloat("u_PointLight[0].constant", 1.0f);
	m_CubeShader->SetFloat("u_PointLight[0].linear", 0.09);
	m_CubeShader->SetFloat("u_PointLight[0].quadratic", 0.032);

	m_DiffuseMap->Bind();
	m_SpecularMap->Bind(1);

	m_CubeVA->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	myo::Renderer::Submit(m_CubeShader, 36, model);
	m_CubeVA->Unbind();
	m_CubeShader->Unbind();

	/// Lamp
	m_LampVA->Bind();
	m_LampShader->Bind();
	m_LampShader->SetFloat3("u_Color", m_LightColor * m_LightIntensity);
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_LightPos) * glm::scale(model, glm::vec3(0.1f));
	myo::Renderer::Submit(m_LampShader, 36, model);
	m_LampVA->Unbind();
	m_LampShader->Unbind();

	myo::Renderer::EndScene();
}

void CubeLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Light Color", glm::value_ptr(m_LightColor));
	ImGui::SliderFloat("Light Intensity", &m_LightIntensity, 0.0f, 10.0f);
	ImGui::End();
}

void CubeLayer::OnEvent(myo::Event& e)
{
	m_CameraController.OnEvent(e);
}
