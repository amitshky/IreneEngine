#include "BlendingTestLayer.h"

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

	m_ScreenShader = myo::CreateRef<myo::Shader>("assets/shaders/FramebufferScreen.shader");

	m_CubeTexture = myo::CreateRef<myo::Texture2D>("assets/textures/container.jpg");
	m_PlaneTexture = myo::CreateRef<myo::Texture2D>("assets/textures/wall.jpg");

	// Quad
	m_QuadVA = myo::CreateRef<myo::VertexArray>();
	m_QuadVB = myo::CreateRef<myo::VertexBuffer>(quadVertices, sizeof(quadVertices));
	m_QuadVB->SetLayout({
		{myo::ShaderDataType::Float2, "a_Position"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
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
	myo::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_Framebuffer = myo::CreateRef<myo::Framebuffer>(fbSpec);
}

void FramebufferLayer::OnUpdate(myo::Timestep ts)
{
	m_Framebuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	myo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	myo::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	myo::Renderer3D::BeginScene(m_CameraController.GetCamera());

	myo::Renderer3D::DrawTexturedCube(m_CubeTexture, { -1.0f, 0.0f, -1.0f }, glm::vec3(1.0f));
	myo::Renderer3D::DrawTexturedCube(m_CubeTexture, { 2.0f, 0.0f, 0.0f }, glm::vec3(1.0f));
	myo::Renderer3D::DrawTexturedPlane(m_PlaneTexture, { 0.0f, -0.5001f, 0.0f }, 1.5708f, { 1.0f, 0.0f, 0.0f }, glm::vec3(8.0f), 2.0f);

	m_Framebuffer->Unbind();
	glDisable(GL_DEPTH_TEST);

	myo::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
	glClear(GL_COLOR_BUFFER_BIT);

	m_ScreenShader->Bind();
	m_QuadVA->Bind();
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	myo::Renderer3D::EndScene();
}

void FramebufferLayer::OnImGuiRender()
{
}

void FramebufferLayer::OnEvent(myo::Event& e)
{
	myo::WindowResizeEvent* resizeEvent = dynamic_cast<myo::WindowResizeEvent*>(&e);
	if (resizeEvent)
		m_Framebuffer->Resize(resizeEvent->GetWidth(), resizeEvent->GetHeight());

	m_CameraController.OnEvent(e);
}
