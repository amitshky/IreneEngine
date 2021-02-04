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

	m_Shader    = irene::Shader::Create("assets/shaders/hdrDemo.shader");
	m_HdrShader = irene::Shader::Create("assets/shaders/hdr.shader");
	m_WoodTex   = irene::Texture2D::Create("assets/textures/wood.png");

	m_Shader->SetInt("u_DiffuseTex", 0);
	m_HdrShader->SetInt("u_HdrBuffer", 0);

	m_Shader->Unbind();
	m_HdrShader->Unbind();

	// lighting info
	m_LightPositions[0] = glm::vec3( 0.0f,  0.0f, -49.5f);
	m_LightPositions[1] = glm::vec3(-1.4f, -1.9f,  -9.0f);
	m_LightPositions[2] = glm::vec3( 0.0f, -1.8f,  -4.0f);
	m_LightPositions[3] = glm::vec3( 0.8f, -1.7f,  -6.0f);

	m_LightColors[0] = glm::vec3(200.0f, 200.0f, 200.0f);
	m_LightColors[1] = glm::vec3(0.1f, 0.0f, 0.0f);
	m_LightColors[2] = glm::vec3(0.0f, 0.0f, 0.2f);
	m_LightColors[3] = glm::vec3(0.0f, 0.1f, 0.0f);

	irene::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	m_HdrFramebuffer = irene::Framebuffer::Create(fbSpec, false);
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	// render scene into floating point framebuffer
	if (irene::FramebufferSpecification spec = m_HdrFramebuffer->GetSpecification();
		m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		m_HdrFramebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	m_HdrFramebuffer->Bind();
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	glm::mat4 viewProj = m_CameraController.GetCamera().GetViewProjectionMatrix();

	m_Shader->Bind();
	m_WoodTex->Bind();

	for (int i = 0; i < m_LightPositions.size(); i++)
	{
		m_Shader->SetFloat3("u_Lights[" + std::to_string(i) + "].Position", m_LightPositions[i]);
		m_Shader->SetFloat3("u_Lights[" + std::to_string(i) + "].Color", m_LightColors[i]);
	}

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -24.0f))
		* glm::scale(glm::mat4(1.0f), glm::vec3(2.5f, 2.5f, 28.5f));
	m_Shader->SetMat4("u_Model", model);
	m_Shader->SetMat4("u_ViewProjection", viewProj);
	m_Shader->SetInt("u_InverseNormals", true);

	m_CubeVA->Bind();
	irene::RenderCommand::Draw(36);
	m_CubeVA->Unbind();
	m_Shader->Unbind();
	m_HdrFramebuffer->Unbind();

	// render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
	irene::RenderCommand::Clear();
	m_HdrFramebuffer->BindColorAttachment();
	m_HdrShader->Bind();
	m_HdrShader->SetInt("u_HdrEnable", m_HdrEnable);
	m_HdrShader->SetFloat("u_Exposure", m_Exposure);

	m_QuadVA->Bind();
	irene::RenderCommand::Draw(6);
	m_QuadVA->Unbind();
	m_HdrShader->Unbind();
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Checkbox("HDR Enable", &m_HdrEnable);
	if (m_HdrEnable)
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

