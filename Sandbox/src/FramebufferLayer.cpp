#include <GLFW/glfw3.h>
#include "FramebufferLayer.h"

FramebufferLayer::FramebufferLayer()
	: Layer("Framebuffer Test"), m_CameraController(16.0f / 9.0f)
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions	// texCoords
		-1.0f,  1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,

		-1.0f,  1.0f,	0.0f, 1.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f
	};

	m_ScreenShader = irene::Shader::Create("assets/shaders/FramebufferScreen.shader");

	m_CubeTexture = irene::Texture2D::Create("assets/textures/container.jpg");
	m_PlaneTexture = irene::Texture2D::Create("assets/textures/wall.jpg");

	// Quad
	m_QuadVA = irene::VertexArray::Create();
	m_QuadVB = irene::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	m_QuadVB->SetLayout({
		{irene::ShaderDataType::Float2, "a_Position"},
		{irene::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_QuadVA->AddVertexBuffer(m_QuadVB);
	m_QuadVB->Unbind();
	m_QuadVA->Unbind();

	m_ScreenShader->SetInt("u_ScreenTexture", 0);
}

FramebufferLayer::~FramebufferLayer()
{
}

void FramebufferLayer::OnAttach()
{
	irene::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_Framebuffer = irene::Framebuffer::Create(fbSpec);
}

void FramebufferLayer::OnDetach()
{
}

void FramebufferLayer::OnUpdate(irene::Timestep ts)
{
	m_Framebuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	irene::Renderer3D::BeginScene(m_CameraController.GetCamera());

	irene::Renderer3D::DrawCube({ -1.0f, 0.0f, -1.0f }, glm::vec3(1.0f), m_CubeTexture);
	irene::Renderer3D::DrawCube({ 2.0f, 0.0f, 0.0f }, glm::vec3(1.0f), m_CubeTexture);
	irene::Renderer3D::DrawPlane({ 0.0f, -0.5001f, 0.0f }, glm::vec3(8.0f), 1.5708f, { 1.0f, 0.0f, 0.0f }, m_PlaneTexture, 2.0f);

	m_Framebuffer->Unbind();
	glDisable(GL_DEPTH_TEST);

	irene::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	glClear(GL_COLOR_BUFFER_BIT);

	m_ScreenShader->Bind();
	m_QuadVA->Bind();
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	irene::Renderer3D::EndScene();
}

void FramebufferLayer::OnImGuiRender()
{
	ImGui::Begin("Framebuffer");
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	irene::Application::Get().GetImGuiLayer()->BlockEvents(!ImGui::IsWindowFocused() || !ImGui::IsWindowHovered());
	ImVec2 viewportPannelSize = ImGui::GetContentRegionAvail();
	ImGui::Image((void*)textureID, ImVec2{ viewportPannelSize.x, viewportPannelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
}

void FramebufferLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
