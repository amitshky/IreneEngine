#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SandboxLayer.h"


SandboxLayer::SandboxLayer()
	: Layer("Sandbox Layer"), m_CameraController(16.0f / 9.0f)
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	float cubeVertices[] = {
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		// top face
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left  
	};

	float quadVertices[] = {
		// positions	// texCoords
		-1.0f,  1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,

		-1.0f,  1.0f,	0.0f, 1.0f,
		 1.0f, -1.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,	1.0f, 1.0f
	};

	m_CubeVA = irene::VertexArray::Create();
	m_CubeVB = irene::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
	m_CubeVB->SetLayout({
		{irene::ShaderDataType::Float3, "a_Position"},
		{irene::ShaderDataType::Float3, "a_Normal"},
		{irene::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_CubeVA->AddVertexBuffer(m_CubeVB);
	m_CubeVB->Unbind();
	m_CubeVA->Unbind();

	m_QuadVA = irene::VertexArray::Create();
	m_QuadVB = irene::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	m_QuadVB->SetLayout({
		{irene::ShaderDataType::Float2, "a_Position"},
		{irene::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_QuadVA->AddVertexBuffer(m_QuadVB);
	m_QuadVB->Unbind();
	m_QuadVA->Unbind();

	m_BloomShader       = irene::Shader::Create("assets/shaders/bloom.shader");
	m_BlurShader        = irene::Shader::Create("assets/shaders/bloomBlur.shader");
	m_LightShader       = irene::Shader::Create("assets/shaders/bloomLightBox.shader");
	m_BloomFinalShader  = irene::Shader::Create("assets/shaders/bloomFinal.shader");
	m_FbScreenTexShader = irene::Shader::Create("assets/shaders/FramebufferScreen.shader");

	m_WoodTex      = irene::Texture2D::Create("assets/textures/wood.png", true);
	m_ContainerTex = irene::Texture2D::Create("assets/textures/container2.png", true);

	m_BloomShader->Bind();
	m_BloomShader->SetInt("u_DiffuseTex", 0);
	m_BlurShader->Bind();
	m_BlurShader->SetInt("u_Image", 0);
	m_BloomFinalShader->Bind();
	m_BloomFinalShader->SetInt("u_Scene", 0);
	m_BloomFinalShader->SetInt("u_BloomBlur", 1);
	m_FbScreenTexShader->Bind();
	m_FbScreenTexShader->SetInt("u_ScreenTexture", 0);

	m_BloomShader->Unbind();
	m_BlurShader->Unbind();
	m_LightShader->Unbind();
	m_BloomFinalShader->Unbind();
	m_FbScreenTexShader->Unbind();

	// lighting info
	m_LightPositions[0] = glm::vec3( 0.0f, 0.5f,  -8.5f);
	m_LightPositions[1] = glm::vec3(-4.0f, 0.5f, -13.0f);
	m_LightPositions[2] = glm::vec3( 3.0f, 0.5f,  -9.0f);
	m_LightPositions[3] = glm::vec3(-0.8f, 2.4f, -11.0f);

	m_LightColors[0] = glm::vec3( 5.0f, 5.0f,  5.0f);
	m_LightColors[1] = glm::vec3(10.0f, 0.0f,  0.0f);
	m_LightColors[2] = glm::vec3( 0.0f, 0.0f, 15.0f);
	m_LightColors[3] = glm::vec3( 0.0f, 5.0f,  0.0f);

	irene::FramebufferSpecification fbSpec;
	fbSpec.Width  = 1280;
	fbSpec.Height = 720;
	fbSpec.Bloom = true;

	m_BloomFramebuffer = irene::Framebuffer::Create(fbSpec);
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	// render scene into floating point framebuffer
	if (irene::FramebufferSpecification spec = m_BloomFramebuffer->GetSpecification();
		m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		m_BloomFramebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	m_BloomFramebuffer->Bind();
	irene::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);

	m_CubeVA->Bind();
	m_BloomShader->Bind();
	glm::mat4 viewProj = m_CameraController.GetCamera().GetViewProjectionMatrix();
	m_BloomShader->SetMat4("u_ViewProjection", viewProj);
	m_BloomShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());

	for (int i = 0; i < m_LightPositions.size(); i++)
	{
		m_BloomShader->SetFloat3("u_Lights[" + std::to_string(i) + "].Position", m_LightPositions[i]);
		m_BloomShader->SetFloat3("u_Lights[" + std::to_string(i) + "].Color", m_LightColors[i]);
	}

	// create one large cube that acts as the floor
	m_WoodTex->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, -10.0));
	model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);

	// then create multiple cubes as the scenery
	m_ContainerTex->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, -10.0));
	model = glm::scale(model, glm::vec3(0.5f));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, -9.0));
	model = glm::scale(model, glm::vec3(0.5f));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -8.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 2.7f, -6.0));
	model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(1.25));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -13.0));
	model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -10.0));
	model = glm::scale(model, glm::vec3(0.5f));
	m_BloomShader->SetMat4("u_Model", model);
	irene::RenderCommand::Draw(36);
	m_BloomShader->Unbind();

	// finally show all the light sources as bright cubes
	m_LightShader->Bind();
	m_LightShader->SetMat4("u_ViewProjection", viewProj);

	for (int i = 0; i < m_LightPositions.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_LightPositions[i]));
		model = glm::scale(model, glm::vec3(0.25f));
		m_LightShader->SetMat4("u_Model", model);
		m_LightShader->SetFloat3("u_LightColor", m_LightColors[i]);
		irene::RenderCommand::Draw(36);
	}
	m_LightShader->Unbind();
	m_CubeVA->Unbind();
	m_BloomFramebuffer->Unbind();

	// blur bright fragments with 2-pass Gaussian blur
	m_QuadVA->Bind();
	m_BlurShader->Bind();
	bool horizontal = true;
	int32_t amount = 10;
	m_BloomFramebuffer->BindColorAttachmentArray(1);
	for (int i = 0; i < amount; i++) // blur the image 10 times, 5 times horizontally and 5 times vertically
	{
		m_BloomFramebuffer->BindPingPongFramebuffer(horizontal);
		m_BlurShader->SetInt("u_Horizontal", horizontal);
		irene::RenderCommand::Draw(6);
		m_BloomFramebuffer->BindPingPongColorAttachment(horizontal);
		horizontal = !horizontal;
	}
	m_BlurShader->Unbind();
	m_BloomFramebuffer->Unbind();

	// render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
	irene::RenderCommand::Clear();
	m_BloomFinalShader->Bind();
	m_BloomFramebuffer->BindColorAttachmentArray(0);
	m_BloomFramebuffer->BindPingPongColorAttachment(!horizontal, 1);
	m_BloomFinalShader->SetInt("u_BloomEnable", m_BloomEnable);
	m_BloomFinalShader->SetFloat("u_Exposure", m_Exposure);
	irene::RenderCommand::Draw(6);
	m_BloomFinalShader->Unbind();
	m_QuadVA->Unbind();

	//// to test individual framebuffer textures (color attachments)
	//m_QuadVA->Bind();
	//irene::RenderCommand::Clear();
	//m_FbScreenTexShader->Bind();
	////m_BloomFramebuffer->BindColorAttachmentArray(1);
	//m_BloomFramebuffer->BindPingPongColorAttachment(!horizontal, 0);
	//irene::RenderCommand::Draw(6);
	//m_QuadVA->Unbind();
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Checkbox("Bloom Enable", &m_BloomEnable);
	ImGui::DragFloat("Exposure", &m_Exposure, 0.1f, 0.0f, 100.0f);
	ImGui::End();
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
	irene::WindowResizeEvent* resize = dynamic_cast<irene::WindowResizeEvent*>(&e);
	if (resize)
		m_ViewportSize = glm::vec2(resize->GetWidth(), resize->GetHeight());
}

