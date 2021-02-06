#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SandboxLayer.h"


SandboxLayer::SandboxLayer()
	: Layer("Sandbox Layer"), m_CameraController(16.0f / 9.0f), m_Generator(0), m_RandDist(0, 1)
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

	// shaders
	m_GeometryPassShader = irene::Shader::Create("assets/shaders/deferredShadingGBuffer.shader");
	m_LightingPassShader = irene::Shader::Create("assets/shaders/deferredShading.shader");
	m_LightBoxShader     = irene::Shader::Create("assets/shaders/deferredShadingLightBox.shader");
	m_TestShader         = irene::Shader::Create("assets/shaders/debug.shader");

	m_LightingPassShader->Bind();
	m_LightingPassShader->SetInt("u_PositionGBuff", 0);
	m_LightingPassShader->SetInt("u_NormalGBuff", 1);
	m_LightingPassShader->SetInt("u_AlbedoSpecGBuff", 2);
	m_TestShader->Bind();
	m_TestShader->SetInt("u_PositionGBuff", 0);
	m_TestShader->SetInt("u_NormalGBuff", 1);
	m_TestShader->SetInt("u_AlbedoSpecGBuff", 2);

	m_GeometryPassShader->Unbind();
	m_LightingPassShader->Unbind();
	m_LightBoxShader->Unbind();
	m_TestShader->Unbind();

	// nanosuit model info
	m_NanosuitModel = irene::Model::Create("assets/3DModels/nanosuit/nanosuit.obj");
	m_NanosuitPositions[0] = glm::vec3(-3.0, -1.75, -7.0);
	m_NanosuitPositions[1] = glm::vec3( 0.0, -1.75, -7.0);
	m_NanosuitPositions[2] = glm::vec3( 3.0, -1.75, -7.0);
	m_NanosuitPositions[3] = glm::vec3(-3.0, -1.75, -4.0);
	m_NanosuitPositions[4] = glm::vec3( 0.0, -1.75, -4.0);
	m_NanosuitPositions[5] = glm::vec3( 3.0, -1.75, -4.0);
	m_NanosuitPositions[6] = glm::vec3(-3.0, -1.75, -2.0);
	m_NanosuitPositions[7] = glm::vec3( 0.0, -1.75, -2.0);
	m_NanosuitPositions[8] = glm::vec3( 3.0, -1.75, -2.0);

	// G-Buffer init
	glCreateFramebuffers(1, &m_GBufferFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_GBufferFBO);
	// position color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_PositionBuff);
	glBindTexture(GL_TEXTURE_2D, m_PositionBuff);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1280, 720, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_PositionBuff, 0);
	// normal color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_NormalBuff);
	glBindTexture(GL_TEXTURE_2D, m_NormalBuff);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1280, 720, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_NormalBuff, 0);
	// color + specular color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_AlbedoSpecBuff);
	glBindTexture(GL_TEXTURE_2D, m_AlbedoSpecBuff);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_AlbedoSpecBuff, 0);

	uint32_t attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	// depth attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthBuffer);
	glBindTexture(GL_TEXTURE_2D, m_DepthBuffer);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, 1280, 720);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer, 0);

	CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// lighting info
	constexpr int32_t numLights = 32;
	for (int i = 0; i < numLights; i++)
	{
		float xPos = m_RandDist(m_Generator) * 6.0f - 3.0f;
		float yPos = m_RandDist(m_Generator) * 6.0f - 3.0f;
		float zPos = m_RandDist(m_Generator) * 6.0f - 7.0f;
		m_LightPositions[i] = glm::vec3(xPos, yPos, zPos);

		float rCol = m_RandDist(m_Generator) * 0.5f + 0.5f; // between 0.5f and 1.0f
		float gCol = m_RandDist(m_Generator) * 0.5f + 0.5f;	// between 0.5f and 1.0f
		float bCol = m_RandDist(m_Generator) * 0.5f + 0.5f;	// between 0.5f and 1.0f
		m_LightColors[i] = glm::vec3(rCol, gCol, bCol);
	}
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	glDisable(GL_BLEND);
	// geometry pass: render scene's geometry/color data into gbuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_GBufferFBO);
	irene::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);
	irene::Renderer::BeginScene(m_CameraController.GetCamera());
	glm::mat4 model = glm::mat4(1.0f);
	for (int i = 0; i < m_NanosuitPositions.size(); i++)
	{
		model = glm::translate(glm::mat4(1.0f), m_NanosuitPositions[i])
			  * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		m_NanosuitModel->Draw(m_GeometryPassShader, model);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// lighting pass: calculate lighting by iterating over a screen filled quad pixel by pixel using gbuffer content
	irene::RenderCommand::Clear();
	m_LightingPassShader->Bind();
	glBindTextureUnit(0, m_PositionBuff);
	glBindTextureUnit(1, m_NormalBuff);
	glBindTextureUnit(2, m_AlbedoSpecBuff);
	for (int i = 0; i < m_LightPositions.size(); i++)
	{
		m_LightingPassShader->SetFloat3("u_Lights[" + std::to_string(i) + "].Position", m_LightPositions[i]);
		m_LightingPassShader->SetFloat3("u_Lights[" + std::to_string(i) + "].Color", m_LightColors[i]);
		// attenuation parameters
		constexpr float linear    = 0.7f;
		constexpr float quadratic = 1.8f;
		m_LightingPassShader->SetFloat("u_Lights[" + std::to_string(i) + "].Linear", linear);
		m_LightingPassShader->SetFloat("u_Lights[" + std::to_string(i) + "].Quadratic", quadratic);
	}
	m_LightingPassShader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());
	m_QuadVA->Bind();
	irene::RenderCommand::Draw(6);
	m_QuadVA->Unbind();
	m_LightingPassShader->Unbind();

	// copy content of geometry's depth buffer to default framebuffer's depth buffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_GBufferFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
	// blit to default framebuffer
	glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// render lights on top of the scene
	m_CubeVA->Bind();
	m_LightBoxShader->Bind();
	glm::mat4 viewProj = m_CameraController.GetCamera().GetViewProjectionMatrix();
	m_LightBoxShader->SetMat4("u_ViewProjection", viewProj);
	for (int i = 0; i < m_LightPositions.size(); i++)
	{
		model = glm::translate(glm::mat4(1.0f), m_LightPositions[i])
			  * glm::scale(glm::mat4(1.0f), glm::vec3(0.125f));
		m_LightBoxShader->SetMat4("u_Model", model);
		m_LightBoxShader->SetFloat3("u_LightColor", m_LightColors[i]);
		irene::RenderCommand::Draw(36);
	}
	m_LightBoxShader->Unbind();
	m_CubeVA->Unbind();

	// for debugging
	//irene::RenderCommand::Clear();
	//m_TestShader->Bind();
	//glBindTextureUnit(0, m_PositionBuff);
	//glBindTextureUnit(1, m_NormalBuff);
	//glBindTextureUnit(2, m_AlbedoSpecBuff);
	//m_QuadVA->Bind();
	//irene::RenderCommand::Draw(6);
	//m_QuadVA->Unbind();

	irene::Renderer::EndScene();
	glEnable(GL_BLEND);
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
}
