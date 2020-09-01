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

	float planeVertices[] = {
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};

	// Cube
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

	// Plane
	m_PlaneVA = irene::VertexArray::Create();
	m_PlaneVB = irene::VertexBuffer::Create(planeVertices, sizeof(planeVertices));
	m_PlaneVB->SetLayout({
		{irene::ShaderDataType::Float3, "a_Position"},
		{irene::ShaderDataType::Float3, "a_Normal"},
		{irene::ShaderDataType::Float2, "a_TexCoords"}
	});
	m_PlaneVA->AddVertexBuffer(m_PlaneVB);
	m_PlaneVB->Unbind();
	m_PlaneVA->Unbind();


	glCreateFramebuffers(1, &m_DepthMapFBO);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthMap);
	glBindTexture(GL_TEXTURE_2D, m_DepthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_ShadowWidth, m_ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach the depth map to framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap, 0);
	// we are not reading or writing to the color attachment
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_Texture = irene::Texture2D::Create("assets/textures/wood.png");

	m_Shader = irene::Shader::Create("assets/shaders/shadowMapping.shader");
	m_SimpleDepthShader = irene::Shader::Create("assets/shaders/shadowMappingDepth.shader");
	m_Shader->Bind();
	m_Shader->SetInt("u_DiffuseTex", 0);
	m_Shader->SetInt("u_ShadowMap", 1);
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(irene::Timestep ts)
{
	irene::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	irene::RenderCommand::Clear();

	m_CameraController.OnUpdate(ts);

	float nearPlane = 1.0f, farPlane = 7.5f;
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
	glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	// 1. render depth of  scene to texture
	m_SimpleDepthShader->Bind();
	m_SimpleDepthShader->SetMat4("u_LightSpaceMatrix", lightSpaceMatrix);

	irene::RenderCommand::SetViewport(0, 0, m_ShadowWidth, m_ShadowHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_Texture->Bind();
	RenderScene(m_SimpleDepthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	 //2. render scene as normal using generated depth map
	
	irene::RenderCommand::SetViewport(0, 0, m_Width, m_Height);
	irene::RenderCommand::Clear();

	m_Shader->Bind();
	m_Shader->SetMat4("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
	m_Shader->SetFloat3("u_ViewPos", m_CameraController.GetCamera().GetPosition());
	m_Shader->SetFloat3("u_LightPos", lightPos);
	m_Shader->SetMat4("u_LightSpaceMatrix", lightSpaceMatrix);
	m_Texture->Bind();
	glBindTextureUnit(1, m_DepthMap);
	RenderScene(m_Shader);

}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(irene::Event& e)
{
	m_CameraController.OnEvent(e);
	irene::WindowResizeEvent* resizeEvent = dynamic_cast<irene::WindowResizeEvent*>(&e);
	if (resizeEvent)
	{
		m_Width = resizeEvent->GetWidth();
		m_Height = resizeEvent->GetHeight();
	}
}

void SandboxLayer::RenderScene(const irene::Ref<irene::Shader>& shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	shader->SetMat4("u_Model", model);
	m_PlaneVA->Bind();
	irene::RenderCommand::Draw(6);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f))
		* glm::scale(model, glm::vec3(0.5f));
	shader->SetMat4("u_Model", model);
	m_CubeVA->Bind();
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0f))
		* glm::scale(model, glm::vec3(0.5f));
	shader->SetMat4("u_Model", model);
	m_CubeVA->Bind();
	irene::RenderCommand::Draw(36);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.35f, 2.0f))
		* glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)))
		* glm::scale(model, glm::vec3(0.5f));
	shader->SetMat4("u_Model", model);
	m_CubeVA->Bind();
	irene::RenderCommand::Draw(36);
	shader->Unbind();
	m_CubeVA->Unbind();
}
