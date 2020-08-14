#include "BlendingTestLayer.h"

#include <GLFW/glfw3.h>
#include "FramebufferLayer.h"

FramebufferLayer::FramebufferLayer()
	: Layer("Framebuffer Test"), m_CameraController(16.0f / 9.0f)
{
	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float planeVertices[] = {
		// positions          // texture Coords 
		 5.0f, -0.5001f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5001f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5001f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5001f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5001f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5001f, -5.0f,  2.0f, 2.0f
	};

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions	// texCoords
		-1.0f,  1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,

		-1.0f,  1.0f,	0.0f, 1.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f
	};

	m_Shader = myo::CreateRef<myo::Shader>("assets/shaders/Framebuffer.shader");
	m_ScreenShader = myo::CreateRef<myo::Shader>("assets/shaders/FramebufferScreen.shader");

	/// Cube
	m_CubeVA = myo::CreateRef<myo::VertexArray>();
	m_CubeVB = myo::CreateRef<myo::VertexBuffer>(cubeVertices, sizeof(cubeVertices));
	m_CubeVB->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_CubeVA->AddVertexBuffer(m_CubeVB);

	m_CubeTexture = myo::CreateRef<myo::Texture2D>("assets/textures/container.jpg");

	m_CubeVB->Unbind();
	m_CubeVA->Unbind();
	
	/// Ground Plane
	m_PlaneVA = myo::CreateRef<myo::VertexArray>();
	m_PlaneVB = myo::CreateRef<myo::VertexBuffer>(planeVertices, sizeof(planeVertices));
	m_PlaneVB->SetLayout({
		{myo::ShaderDataType::Float3, "a_Position"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_PlaneVA->AddVertexBuffer(m_PlaneVB);

	m_PlaneTexture = myo::CreateRef<myo::Texture2D>("assets/textures/wall.jpg");

	m_PlaneVB->Unbind();
	m_PlaneVA->Unbind();

	/// Quad
	m_QuadVA = myo::CreateRef<myo::VertexArray>();
	m_QuadVB = myo::CreateRef<myo::VertexBuffer>(quadVertices, sizeof(quadVertices));
	m_QuadVB->SetLayout({
		{myo::ShaderDataType::Float2, "a_Position"},
		{myo::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_QuadVA->AddVertexBuffer(m_QuadVB);
	m_QuadVB->Unbind();
	m_QuadVA->Unbind();

	m_Shader->SetInt("u_Texture", 0);
	m_ScreenShader->SetInt("u_ScreenTexture", 0);
	
	/// Framebuffer
	//glCreateFramebuffers(1, &m_RendererID);

	//glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
	//glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glCreateRenderbuffers(1, &m_DepthAttachment);
	//glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);

	//glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
	//
	//CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete");
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	myo::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_CameraController.OnUpdate(ts);
	myo::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Shader->Bind();

	/// Cubes
	m_CubeVA->Bind();
	m_CubeTexture->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
	myo::Renderer::Submit(m_Shader, 36, model);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	myo::Renderer::Submit(m_Shader, 36, model);
	m_CubeVA->Unbind();

	/// floor
	m_PlaneVA->Bind();
	m_PlaneTexture->Bind();
	model = glm::mat4(1.0f);
	myo::Renderer::Submit(m_Shader, 6, model);
	m_PlaneVA->Unbind();

	m_Framebuffer->Unbind();
	glDisable(GL_DEPTH_TEST);

	myo::RenderCommand::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	glClear(GL_COLOR_BUFFER_BIT);

	m_ScreenShader->Bind();
	m_QuadVA->Bind();
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetColorAttachmentRendererID());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	myo::Renderer::EndScene();
}

void FramebufferLayer::OnImGuiRender()
{
}

void FramebufferLayer::OnEvent(myo::Event& e)
{
	m_CameraController.OnEvent(e);
}
