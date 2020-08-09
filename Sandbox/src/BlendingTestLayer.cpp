#include "BlendingTestLayer.h"

#include <GLFW/glfw3.h>

BlendingTestLayer::BlendingTestLayer()
	: Layer("Blending Test"), m_CameraController(16.0f / 9.0f)
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

	m_TransparentPlanePosition.push_back(glm::vec3(0.3f, 0.0f, 1.8f));
	m_TransparentPlanePosition.push_back(glm::vec3(0.5f, 0.0f, 1.5f));
	m_TransparentPlanePosition.push_back(glm::vec3(0.5f, 0.0f, -1.4f));

	/// Cube
	m_CubeVA = myo::CreateRef<myo::VertexArray>();
	m_CubeVB = myo::CreateRef<myo::VertexBuffer>(vertices, sizeof(vertices));
	m_CubeVB->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float3, "a_Normal"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_CubeVA->AddVertexBuffer(m_CubeVB);

	m_CubeShader = myo::CreateRef<myo::Shader>("assets/shaders/texture.shader");
	m_CubeShader->Bind();
	m_DiffuseMap = myo::CreateRef<myo::Texture2D>("assets/textures/container2.png");
	m_CubeShader->SetInt("u_Texture", 0);

	m_CubeShader->Unbind();
	m_CubeVB->Unbind();
	m_CubeVA->Unbind();

	/// Transparent plane
	m_TransparentVA = myo::CreateRef<myo::VertexArray>();
	m_TransparentVB = myo::CreateRef<myo::VertexBuffer>(vertices, sizeof(vertices));
	m_TransparentVB->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float3, "a_Normal"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_TransparentVA->AddVertexBuffer(m_TransparentVB);

	m_TransparentShader = myo::CreateRef<myo::Shader>("assets/shaders/texture.shader");
	m_TransparentShader->Bind();
	m_TransparentTexture = myo::CreateRef<myo::Texture2D>("assets/textures/transparentWindow.png");
	m_TransparentShader->SetInt("u_Texture", 0);

	m_TransparentShader->Unbind();
	m_TransparentVB->Unbind();
	m_TransparentVA->Unbind();
}

BlendingTestLayer::~BlendingTestLayer()
{
}

void BlendingTestLayer::OnUpdate(myo::Timestep ts)
{
	myo::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	myo::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	myo::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 model;

	m_CubeShader->Bind();
	m_DiffuseMap->Bind();
	m_CubeVA->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	myo::Renderer::Submit(m_CubeShader, 36, model);
	model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0f), { 0.5f, 0.0f, -1.2f }) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	myo::Renderer::Submit(m_CubeShader, 36, model);
	m_CubeVA->Unbind();
	m_CubeShader->Unbind();

	// sort the transparent windows before rendering
	std::map<float, glm::vec3> sorted; // map sorts data based on 'key' (key here is distance)
	for (unsigned int i = 0; i < m_TransparentPlanePosition.size(); i++)
	{
		float distance = glm::length(m_CameraController.GetCamera().GetPosition() - m_TransparentPlanePosition[i]);
		sorted[distance] = m_TransparentPlanePosition[i];
	}

	m_TransparentShader->Bind();
	m_TransparentTexture->Bind();
	m_TransparentVA->Bind();
	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, it->second);
		myo::Renderer::Submit(m_TransparentShader, 6, model);
	}
	m_TransparentVA->Unbind();
	m_TransparentShader->Unbind();

	myo::Renderer::EndScene();
}

void BlendingTestLayer::OnImGuiRender()
{
}

void BlendingTestLayer::OnEvent(myo::Event& e)
{
	m_CameraController.OnEvent(e);
}
