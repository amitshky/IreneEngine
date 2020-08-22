#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include "CubemapLayer.h"


CubemapLayer::CubemapLayer()
	: Layer("Framebuffer Test"), m_CameraController(16.0f / 9.0f)
{
	float skyboxVertices[] = {
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	
	m_SkyboxVA = irene::VertexArray::Create();
	m_SkyboxVB = irene::VertexBuffer::Create(skyboxVertices, sizeof(skyboxVertices));
	m_SkyboxVB->SetLayout({
		{ irene::ShaderDataType::Float3, "a_Position" }
	});
	m_SkyboxVA->AddVertexBuffer(m_SkyboxVB);

	m_SkyboxShader = irene::Shader::Create("assets/shaders/Cubemap.shader");
	m_SkyboxShader->SetInt("u_Skybox", 5);
	m_SkyboxVA->Unbind();
	m_SkyboxVB->Unbind();
	m_SkyboxShader->Unbind();

	std::vector<std::string> faces = 
	{
		"assets/textures/skybox/right.jpg",
		"assets/textures/skybox/left.jpg",
		"assets/textures/skybox/top.jpg",
		"assets/textures/skybox/bottom.jpg",
		"assets/textures/skybox/front.jpg",
		"assets/textures/skybox/back.jpg"
	};
	m_CubemapTexture = irene::Texture2D::Create(faces);
	m_CubeTexture = irene::Texture2D::Create("assets/textures/container2.png");
}

CubemapLayer::~CubemapLayer()
{
}

void CubemapLayer::OnAttach()
{
}

void CubemapLayer::OnDetach()
{
}

void CubemapLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	irene::Renderer3D::BeginScene(m_CameraController.GetCamera());
	irene::Renderer3D::DrawCube(m_CubeTexture, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	irene::Renderer3D::EndScene();

	
	// Render skybox last
	glm::mat4 view = glm::mat4(glm::mat3(m_CameraController.GetCamera().GetViewMatrix()));
	// This removes any translation, but keeps all rotation transformations 
	// so the user can still look around the scene.
	glm::mat4 proj = m_CameraController.GetCamera().GetProjectionMatrix();
	glm::mat4 viewProj = proj * view;
	glDepthFunc(GL_LEQUAL);
	m_SkyboxShader->Bind();
	m_SkyboxShader->SetMat4("u_ViewProjection", viewProj);
	m_SkyboxVA->Bind();
	m_CubemapTexture->Bind(5);
	irene::RenderCommand::Draw(36);
	glDepthFunc(GL_LESS);
}

void CubemapLayer::OnImGuiRender()
{
}

void CubemapLayer::OnEvent(irene::Event& e)
{
}

