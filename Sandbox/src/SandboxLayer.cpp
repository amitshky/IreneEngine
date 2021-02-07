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
	m_GeometryPassShader = irene::Shader::Create("assets/shaders/ssaoGeometry.shader");
	m_LightingPassShader = irene::Shader::Create("assets/shaders/ssaoLighting.shader");
	m_SSAOShader         = irene::Shader::Create("assets/shaders/ssao.shader");
	m_SSAOBlurShader     = irene::Shader::Create("assets/shaders/ssaoBlur.shader");
	m_TestShader         = irene::Shader::Create("assets/shaders/debug.shader");

	m_LightingPassShader->Bind();
	m_LightingPassShader->SetInt("u_PositionGBuff", 0);
	m_LightingPassShader->SetInt("u_NormalGBuff", 1);
	m_LightingPassShader->SetInt("u_AlbedoSpecGBuff", 2);
	m_LightingPassShader->SetInt("u_SSAO", 3);

	m_SSAOShader->Bind();
	m_SSAOShader->SetInt("u_PositionGBuff", 0);
	m_SSAOShader->SetInt("u_NormalGBuff", 1);
	m_SSAOShader->SetInt("u_TexNoise", 2);

	m_SSAOBlurShader->Bind();
	m_SSAOBlurShader->SetInt("u_SSAOInput", 0);
	m_TestShader->Bind();
	m_TestShader->SetInt("u_FboAttachment", 0);
	m_TestShader->Unbind();

	// nanosuit model info
	m_NanosuitModel = irene::Model::Create("assets/3DModels/nanosuit/nanosuit.obj");

	// G-Buffer init
	glCreateFramebuffers(1, &m_GBufferFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_GBufferFBO);
	// position color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_PositionBuff);
	glBindTexture(GL_TEXTURE_2D, m_PositionBuff);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1280, 720, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_PositionBuff, 0);
	// normal color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_NormalBuff);
	glBindTexture(GL_TEXTURE_2D, m_NormalBuff);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1280, 720, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_NormalBuff, 0);
	// color + sepcular color buffer
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
	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// create framebuffer to hold SSAO processing stage
	glCreateFramebuffers(1, &m_SSAOFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAOFBO);
	// SSAO color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_SSAOColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_SSAOColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1280, 720, 0, GL_RED, GL_FLOAT, NULL); // ambient occlusion result is a single greyscale value so GL_RED
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_SSAOColorBuffer, 0);
	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
	// blur stage
	glCreateFramebuffers(1, &m_SSAOBlurFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAOBlurFBO);
	// SSAO blur color buffer
	glCreateTextures(GL_TEXTURE_2D, 1, &m_SSAOBlurColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_SSAOBlurColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1280, 720, 0, GL_RED, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_SSAOBlurColorBuffer, 0);
	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// generate sample kernel for normal-oriented hemisphere
	for (int i = 0; i < 64; i++)
	{
		glm::vec3 randSample(m_RandDist(m_Generator) * 2.0f - 1.0f, // between -1.0f and 1.0f
							 m_RandDist(m_Generator) * 2.0f - 1.0f, // between -1.0f and 1.0f
							 m_RandDist(m_Generator));              // between  0.0f and 1.0f // because hemisphere
		randSample = glm::normalize(randSample);
		randSample *= m_RandDist(m_Generator);
		// distributing the randSamples close the actual fragment
		float scale = (float)i / 64.0f;
		scale = Lerp(0.1f, 1.0f, scale * scale);
		randSample *= scale;
		m_SSAOKernel[i] = randSample;
	}

	// generate 4x4 noise texture // used to rotate the sample kernel
	for (int i = 0; i < 16; i++)
	{
		glm::vec3 noise(m_RandDist(m_Generator) * 2.0f - 1.0f,
						m_RandDist(m_Generator) * 2.0f - 1.0f,
						0.0f); // rotate around z-axis in tangent space
		m_SSAONoise[i] = noise;
	}
	glCreateTextures(GL_TEXTURE_2D, 1, &m_NoiseTexture);
	glBindTexture(GL_TEXTURE_2D, m_NoiseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 4, 4, 0, GL_RGB, GL_FLOAT, &m_SSAONoise[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

	m_GeometryPassShader->Bind();
	glm::mat4 projection = m_CameraController.GetCamera().GetProjectionMatrix();
	glm::mat4 view = m_CameraController.GetCamera().GetViewMatrix();
	m_GeometryPassShader->SetMat4("u_Projection", projection);
	m_GeometryPassShader->SetMat4("u_View", view);
	// room cube
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0f), { 0.0f,  3.0f, 0.0f })
		  * glm::scale(glm::mat4(1.0f), glm::vec3(4.0f));
	m_GeometryPassShader->SetMat4("u_Model", model);
	m_GeometryPassShader->SetInt("u_InvertedNormals", true);
	m_CubeVA->Bind();
	irene::RenderCommand::Draw(36);
	m_CubeVA->Unbind();

	// nanosuit model
	m_GeometryPassShader->SetInt("u_InvertedNormals", false);
	model = glm::translate(glm::mat4(1.0f), { 0.0f, -3.7f, 0.0f })
		  * glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0))
		  * glm::scale(glm::mat4(1.0f), glm::vec3(0.04f));
	m_NanosuitModel->Draw(m_GeometryPassShader, model);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// generate SSAO texture
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAOFBO);
	glClear(GL_COLOR_BUFFER_BIT);
	m_SSAOShader->Bind();
	// send kernel + rotation
	for (int i = 0; i < 64; i++)
		m_SSAOShader->SetFloat3("samples[" + std::to_string(i) + "]", m_SSAOKernel[i]);
	m_SSAOShader->SetMat4("u_Projection", projection);
	glBindTextureUnit(0, m_PositionBuff);
	glBindTextureUnit(1, m_NormalBuff);
	glBindTextureUnit(2, m_NoiseTexture);
	m_QuadVA->Bind();
	irene::RenderCommand::Draw(6);
	m_QuadVA->Unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// blur SSAO texture to remove noise
	glBindFramebuffer(GL_FRAMEBUFFER, m_SSAOBlurFBO);
	glClear(GL_COLOR_BUFFER_BIT);
	m_SSAOBlurShader->Bind();
	glBindTextureUnit(0, m_SSAOColorBuffer);
	m_QuadVA->Bind();
	irene::RenderCommand::Draw(6);
	m_QuadVA->Unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// lighting pass
	irene::RenderCommand::Clear();
	m_LightingPassShader->Bind();
	// send light relevant uniforms
	glm::vec3 lightPosView = glm::vec3(view * glm::vec4(m_LightPos, 1.0));
	m_LightingPassShader->SetFloat3("u_Light.Position", lightPosView);
	m_LightingPassShader->SetFloat3("u_Light.Color", m_LightColor);
	// Update attenuation parameters
	constexpr float linear    = 0.09f;
	constexpr float quadratic = 0.032f;
	m_LightingPassShader->SetFloat("u_Light.Linear", linear);
	m_LightingPassShader->SetFloat("u_Light.Quadratic", quadratic);
	glBindTextureUnit(0, m_PositionBuff);
	glBindTextureUnit(1, m_NormalBuff);
	glBindTextureUnit(2, m_AlbedoSpecBuff);
	glBindTextureUnit(3, m_SSAOBlurColorBuffer);
	m_QuadVA->Bind();
	irene::RenderCommand::Draw(6);
	m_QuadVA->Unbind();

	// for debugging
	//irene::RenderCommand::Clear();
	//m_TestShader->Bind();
	//glBindTextureUnit(0, m_SSAOColorBuffer);
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
